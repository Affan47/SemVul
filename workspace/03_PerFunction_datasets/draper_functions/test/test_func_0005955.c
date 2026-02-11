CollectStats(HeapObject* obj, HistogramInfo* info) {
  InstanceType type = obj->map()->instance_type();
  ASSERT(0 <= type && type <= LAST_TYPE);
  if (!FreeListNode::IsFreeListNode(obj)) {
    info[type].increment_number(1);
    info[type].increment_bytes(obj->Size());
  }
}
