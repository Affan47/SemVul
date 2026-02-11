UpdatePointers() {
#ifdef DEBUG
  ASSERT(state_ == ENCODE_FORWARDING_ADDRESSES);
  state_ = UPDATE_POINTERS;
#endif
  UpdatingVisitor updating_visitor;
  Heap::IterateRoots(&updating_visitor, VISIT_ONLY_STRONG);
  GlobalHandles::IterateWeakRoots(&updating_visitor);

  int live_maps = IterateLiveObjects(Heap::map_space(),
                                     &UpdatePointersInOldObject);
  int live_pointer_olds = IterateLiveObjects(Heap::old_pointer_space(),
                                             &UpdatePointersInOldObject);
  int live_data_olds = IterateLiveObjects(Heap::old_data_space(),
                                          &UpdatePointersInOldObject);
  int live_codes = IterateLiveObjects(Heap::code_space(),
                                      &UpdatePointersInOldObject);
  int live_cells = IterateLiveObjects(Heap::cell_space(),
                                      &UpdatePointersInOldObject);
  int live_news = IterateLiveObjects(Heap::new_space(),
                                     &UpdatePointersInNewObject);


  LargeObjectIterator it(Heap::lo_space());
  for (HeapObject* obj = it.next(); obj != NULL; obj = it.next())
    UpdatePointersInNewObject(obj);

  USE(live_maps);
  USE(live_pointer_olds);
  USE(live_data_olds);
  USE(live_codes);
  USE(live_cells);
  USE(live_news);
  ASSERT(live_maps == live_map_objects_);
  ASSERT(live_data_olds == live_old_data_objects_);
  ASSERT(live_pointer_olds == live_old_pointer_objects_);
  ASSERT(live_codes == live_code_objects_);
  ASSERT(live_cells == live_cell_objects_);
  ASSERT(live_news == live_young_objects_);
}
