PrintTestList(CcTest* current) {
  if (current == NULL) return;
  PrintTestList(current->prev());
  if (current->dependency() != NULL) {
    printf("%s/%s<%s\n",
           current->file(), current->name(), current->dependency());
  } else {
    printf("%s/%s<\n", current->file(), current->name());
  }
}
