DB_Format(DB_DRIVER *driver, GB_VALUE *arg, DB_FORMAT_CALLBACK add)
{
  static char buffer[32];

  char *s;
  int l;
  int i;

  if (arg->type == GB_T_VARIANT)
    GB.Conv(arg, ((GB_VARIANT *)arg)->value.type);

	if (arg->type == (GB_TYPE)CLASS_Blob)
	{
		(*driver->FormatBlob)((DB_BLOB *)(((GB_OBJECT *)arg)->value), add);
		return;
	}

  if (!(*driver->Format)(arg, add))
  {
    switch (arg->type)
    {
      case GB_T_BOOLEAN:

        if (VALUE((GB_BOOLEAN *)arg))
          add("TRUE", 4);
        else
          add("FALSE", 5);

        return;

      case GB_T_BYTE:
      case GB_T_SHORT:
      case GB_T_INTEGER:

        l = sprintf(buffer, "%d", VALUE((GB_INTEGER *)arg));
        add(buffer, l);
        return;

      case GB_T_LONG:

        l = sprintf(buffer, "%" PRId64, VALUE((GB_LONG *)arg));
        add(buffer, l);
        return;

      case GB_T_FLOAT:

        GB.NumberToString(FALSE, VALUE((GB_FLOAT *)arg), NULL, &s, &l);
        add(s, l);

        return;

      case GB_T_STRING:
      case GB_T_CSTRING:

        s = VALUE((GB_STRING *)arg).addr + VALUE((GB_STRING *)arg).start;
        l = VALUE((GB_STRING *)arg).len;

        add("'", 1);

        for (i = 0; i < l; i++, s++)
        {
          add(s, 1);
          if (*s == '\'' || *s == '\\')
            add(s, 1);
        }

        add("'", 1);
        return;

      case GB_T_NULL:

        add("NULL", 4);
        return;

      default:
      	fprintf(stderr, "gb.db: DB_Format: unsupported datatype: %d\n", (int)arg->type);
        return;
    }
  }
}
