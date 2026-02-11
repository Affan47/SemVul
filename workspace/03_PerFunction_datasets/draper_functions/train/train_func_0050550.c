read_structure(STREAM *stream, CLASS *class, char *base)
{
	int i, n;
	CLASS_DESC *desc;
	char *addr;
	CTYPE ctype;

	for (n = 0; n < class->n_desc; n++)
	{
		desc = class->table[n].desc;
		ctype = desc->variable.ctype;
		addr = base + desc->variable.offset;

		if (ctype.id == TC_STRUCT)
		{
			read_structure(stream, class->load->class_ref[ctype.value], addr);
		}
		else if (ctype.id == TC_ARRAY)
		{
			CLASS_ARRAY *adesc = class->load->array[ctype.value];
			int size = CLASS_sizeof_ctype(class, adesc->ctype);

			for (i = 0; i < CARRAY_get_static_count(adesc); i++)
			{
				read_value_ctype(stream, desc->variable.class, adesc->ctype, addr);
				addr += size;
			}
		}
		else
		{
			read_value_ctype(stream, desc->variable.class, ctype, addr);
		}
	}
}
