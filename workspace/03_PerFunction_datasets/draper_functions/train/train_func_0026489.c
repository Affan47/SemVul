pop_arguments(glui32 count, glui32 addr)
{
  int ix;
  glui32 argptr;
  glui32 *array;

  #define MAXARGS (32)
  static glui32 statarray[MAXARGS];
  static glui32 *dynarray = NULL;
  static glui32 dynarray_size = 0;

  if (count == 0)
    return NULL;

  if (count <= MAXARGS) {

    array = statarray;
  }
  else {
    if (!dynarray) {
      dynarray_size = count+8;
      dynarray = glulx_malloc(sizeof(glui32) * dynarray_size);
      if (!dynarray)
        fatal_error("Unable to allocate function arguments.");
      array = dynarray;
    }
    else {
      if (dynarray_size >= count) {

        array = dynarray;
      }
      else {
        dynarray_size = count+8;
        dynarray = glulx_realloc(dynarray, sizeof(glui32) * dynarray_size);
        if (!dynarray)
          fatal_error("Unable to reallocate function arguments.");
        array = dynarray;
      }
    }
  }

  if (!addr) {
    if (stackptr < valstackbase+4*count)
      fatal_error("Stack underflow in arguments.");
    stackptr -= 4*count;
    for (ix=0; ix<count; ix++) {
      argptr = stackptr+4*((count-1)-ix);
      array[ix] = Stk4(argptr);
    }
  }
  else {
    for (ix=0; ix<count; ix++) {
      array[ix] = Mem4(addr);
      addr += 4;
    }
  }

  return array;
}
