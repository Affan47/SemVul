RCTdata_free(void** ptr)
{
  RCTdata** data = (RCTdata**) ptr;
  assert(data != NULL);
  if (data == NULL) {
    return;
  }
  assert((*data) != NULL);
  if ((*data) == NULL) {
    return;
  }
  free((*data));
  (*data) = NULL;
}
