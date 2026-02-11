VisitSharedFunctionInfoAndFlushCodeGeneric(
      Map* map, HeapObject* object, bool known_flush_code_candidate) {
    SharedFunctionInfo* shared = reinterpret_cast<SharedFunctionInfo*>(object);

    if (shared->IsInobjectSlackTrackingInProgress()) shared->DetachInitialMap();

    if (!known_flush_code_candidate) {
      known_flush_code_candidate = IsFlushable(shared);
      if (known_flush_code_candidate) FlushCode::AddCandidate(shared);
    }

    VisitSharedFunctionInfoFields(object, known_flush_code_candidate);
  }
