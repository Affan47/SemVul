createInternalizePass(ArrayRef<const char *> ExportList) {
  return new InternalizePass(ExportList);
}
