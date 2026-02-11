varray_grow (varray_type va, size_t n)
{
  size_t old_elements = va->num_elements;
  if (n != old_elements)
    {
      size_t elem_size = element[va->type].size;
      size_t old_data_size = old_elements * elem_size;
      size_t data_size = n * elem_size;
#ifdef GATHER_STATISTICS
      struct varray_descriptor *desc = varray_descriptor (va->name);
      varray_type oldva = va;

      if (data_size > old_data_size)
        desc->allocated += data_size - old_data_size;
      desc->resized ++;
#endif


      if (element[va->type].uses_ggc)
	va = ggc_realloc (va, VARRAY_HDR_SIZE + data_size);
      else
	va = xrealloc (va, VARRAY_HDR_SIZE + data_size);
      va->num_elements = n;
      if (n > old_elements)
	memset (&va->data.c[old_data_size], 0, data_size - old_data_size);
#ifdef GATHER_STATISTICS
      if (oldva != va)
        desc->copied++;
#endif
    }

  return va;
}
