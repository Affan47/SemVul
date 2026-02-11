GetFunctionName() const {
  IsDeadCheck("v8::CpuProfileNode::GetFunctionName");
  const i::ProfileNode* node = reinterpret_cast<const i::ProfileNode*>(this);
  const i::CodeEntry* entry = node->entry();
  if (!entry->has_name_prefix()) {
    return Handle<String>(ToApi<String>(
        i::Factory::LookupAsciiSymbol(entry->name())));
  } else {
    return Handle<String>(ToApi<String>(i::Factory::NewConsString(
        i::Factory::LookupAsciiSymbol(entry->name_prefix()),
        i::Factory::LookupAsciiSymbol(entry->name()))));
  }
}
