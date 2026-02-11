Scavenge() {
#ifdef DEBUG
  if (FLAG_enable_slow_asserts) VerifyNonPointerSpacePointers();
#endif

  gc_state_ = SCAVENGE;

  SwitchScavengingVisitorsTableIfProfilingWasEnabled();

  Page::FlipMeaningOfInvalidatedWatermarkFlag(this);
#ifdef DEBUG
  VerifyPageWatermarkValidity(old_pointer_space_, ALL_VALID);
  VerifyPageWatermarkValidity(map_space_, ALL_VALID);
#endif


  old_pointer_space_->FlushTopPageWatermark();
  map_space_->FlushTopPageWatermark();


  LOG(isolate_, ResourceEvent("scavenge", "begin"));


  isolate_->descriptor_lookup_cache()->Clear();


  intptr_t survived_watermark = PromotedSpaceSize();

  CheckNewSpaceExpansionCriteria();


  new_space_.Flip();
  new_space_.ResetAllocationInfo();


  Address new_space_front = new_space_.ToSpaceLow();
  promotion_queue_.Initialize(new_space_.ToSpaceHigh());

  is_safe_to_read_maps_ = false;
  ScavengeVisitor scavenge_visitor(this);

  IterateRoots(&scavenge_visitor, VISIT_ALL_IN_SCAVENGE);


  IterateDirtyRegions(old_pointer_space_,
                      &Heap::IteratePointersInDirtyRegion,
                      &ScavengePointer,
                      WATERMARK_CAN_BE_INVALID);

  IterateDirtyRegions(map_space_,
                      &IteratePointersInDirtyMapsRegion,
                      &ScavengePointer,
                      WATERMARK_CAN_BE_INVALID);

  lo_space_->IterateDirtyRegions(&ScavengePointer);


  HeapObjectIterator cell_iterator(cell_space_);
  for (HeapObject* cell = cell_iterator.next();
       cell != NULL; cell = cell_iterator.next()) {
    if (cell->IsJSGlobalPropertyCell()) {
      Address value_address =
          reinterpret_cast<Address>(cell) +
          (JSGlobalPropertyCell::kValueOffset - kHeapObjectTag);
      scavenge_visitor.VisitPointer(reinterpret_cast<Object**>(value_address));
    }
  }


  scavenge_visitor.VisitPointer(BitCast<Object**>(&global_contexts_list_));

  new_space_front = DoScavenge(&scavenge_visitor, new_space_front);
  isolate_->global_handles()->IdentifyNewSpaceWeakIndependentHandles(
      &IsUnscavengedHeapObject);
  isolate_->global_handles()->IterateNewSpaceWeakIndependentRoots(
      &scavenge_visitor);
  new_space_front = DoScavenge(&scavenge_visitor, new_space_front);


  UpdateNewSpaceReferencesInExternalStringTable(
      &UpdateNewSpaceReferenceInExternalStringTableEntry);

  LiveObjectList::UpdateReferencesForScavengeGC();
  isolate()->runtime_profiler()->UpdateSamplesAfterScavenge();

  ASSERT(new_space_front == new_space_.top());

  is_safe_to_read_maps_ = true;


  new_space_.set_age_mark(new_space_.top());


  IncrementYoungSurvivorsCounter(static_cast<int>(
      (PromotedSpaceSize() - survived_watermark) + new_space_.Size()));

  LOG(isolate_, ResourceEvent("scavenge", "end"));

  gc_state_ = NOT_IN_GC;
}
