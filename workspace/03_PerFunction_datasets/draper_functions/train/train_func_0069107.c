classify_argument (ffi_type *type, enum x86_64_reg_class classes[],
		   size_t byte_offset)
{
  switch (type->type)
    {
    case FFI_TYPE_UINT8:
    case FFI_TYPE_SINT8:
    case FFI_TYPE_UINT16:
    case FFI_TYPE_SINT16:
    case FFI_TYPE_UINT32:
    case FFI_TYPE_SINT32:
    case FFI_TYPE_UINT64:
    case FFI_TYPE_SINT64:
    case FFI_TYPE_POINTER:
      if (byte_offset + type->size <= 4)
	classes[0] = X86_64_INTEGERSI_CLASS;
      else
	classes[0] = X86_64_INTEGER_CLASS;
      return 1;
    case FFI_TYPE_FLOAT:
      if (byte_offset == 0)
	classes[0] = X86_64_SSESF_CLASS;
      else
	classes[0] = X86_64_SSE_CLASS;
      return 1;
    case FFI_TYPE_DOUBLE:
      classes[0] = X86_64_SSEDF_CLASS;
      return 1;
    case FFI_TYPE_LONGDOUBLE:
      classes[0] = X86_64_X87_CLASS;
      classes[1] = X86_64_X87UP_CLASS;
      return 2;
    case FFI_TYPE_STRUCT:
      {
	const int UNITS_PER_WORD = 8;
	int words = (type->size + UNITS_PER_WORD - 1) / UNITS_PER_WORD;
	ffi_type **ptr;
	int i;
	enum x86_64_reg_class subclasses[MAX_CLASSES];


	if (type->size > 16)
	  return 0;

	for (i = 0; i < words; i++)
	  classes[i] = X86_64_NO_CLASS;


	for (ptr = type->elements; *ptr != NULL; ptr++)
	  {
	    int num;

	    byte_offset = ALIGN (byte_offset, (*ptr)->alignment);

	    num = classify_argument (*ptr, subclasses, byte_offset % 8);
	    if (num == 0)
	      return 0;
	    for (i = 0; i < num; i++)
	      {
		int pos = byte_offset / 8;
		classes[i + pos] =
		  merge_classes (subclasses[i], classes[i + pos]);
	      }

	    byte_offset += (*ptr)->size;
	  }


	for (i = 0; i < words; i++)
	  {


	    if (classes[i] == X86_64_MEMORY_CLASS)
	      return 0;


	    if (classes[i] == X86_64_SSEUP_CLASS
		&& (i == 0 || classes[i - 1] != X86_64_SSE_CLASS))
	      classes[i] = X86_64_SSE_CLASS;


	    if (classes[i] == X86_64_X87UP_CLASS
		&& (i == 0 || classes[i - 1] != X86_64_X87_CLASS))
	      classes[i] = X86_64_SSE_CLASS;
	  }
	return words;
      }

    default:
      FFI_ASSERT(0);
    }
  return 0;
}
