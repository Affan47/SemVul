array_list_expand_internal(struct array_list *arr, int max)
{
  void *t;
  int new_size;

  if(max < arr->size) return 0;
  new_size = json_max(arr->size << 1, max);
  if((t = realloc(arr->array, new_size*sizeof(void*))) == NULL) return -1;
  arr->array = (void**)t;
  (void)memset(arr->array + arr->size, 0, (new_size-arr->size)*sizeof(void*));
  arr->size = new_size;
  return 0;
}
