ap_generator0_array_make(size_t size)
{
  size_t i;
  ap_generator0_array_t array;

  array.size = size;
  array.p = (size==0) ? NULL : (ap_generator0_t*)malloc(size*sizeof(ap_generator0_t));
  for (i=0; i<size; i++){
    array.p[i].linexpr0 = NULL;
  }
  return array;
}
