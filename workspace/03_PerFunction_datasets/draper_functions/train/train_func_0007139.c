Put(Handle<String> source,
                                 Handle<SharedFunctionInfo> function_info) {
  HandleScope scope;
  SetFirstTable(TablePut(source, function_info));
}
