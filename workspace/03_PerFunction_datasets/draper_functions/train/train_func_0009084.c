LookupScript(Handle<String> source,
                                                          Handle<Object> name,
                                                          int line_offset,
                                                          int column_offset) {
  if (!IsEnabled()) {
    return Handle<SharedFunctionInfo>::null();
  }

  return script_.Lookup(source, name, line_offset, column_offset);
}
