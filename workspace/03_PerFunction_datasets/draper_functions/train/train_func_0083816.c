DeregisterAllTables() {
  if (ExceptionTableDeregister) {
    DenseMap<const Function*, void*>::iterator it = AllExceptionTables.begin();
    DenseMap<const Function*, void*>::iterator ite = AllExceptionTables.end();
    for (; it != ite; ++it)
      ExceptionTableDeregister(it->second);
    AllExceptionTables.clear();
  }
}
