HandleWeakDebugInfo(v8::Persistent<v8::Value> obj, void* data) {
  DebugInfoListNode* node = reinterpret_cast<DebugInfoListNode*>(data);


  BreakLocationIterator it(node->debug_info(), ALL_BREAK_LOCATIONS);
  it.ClearAllDebugBreak();
  RemoveDebugInfo(node->debug_info());
#ifdef DEBUG
  node = Debug::debug_info_list_;
  while (node != NULL) {
    ASSERT(node != reinterpret_cast<DebugInfoListNode*>(data));
    node = node->next();
  }
#endif
}
