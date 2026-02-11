buildIndexEntry (PR *pr)
{
  int x;
  int num_fields = get_num_fields (pr->database);
  Index *newIndex;

  freePRIndex (pr);
  newIndex = pr->index;

  newIndex->fields = (char **) xmalloc (sizeof (char *) * num_fields);
  memset (newIndex->fields, 0, sizeof (char *) * num_fields);
  newIndex->buf = NULL;
  for (x = 0; x < num_fields; x++)
    {
      FieldIndex field = getNthField (pr->database, x);
      if (isIndexedFieldIndex (field))
	{
	  const char *fc = field_value (pr, field);

	  if (fieldDefForIndex (field)->datatype == Date)
	    {
	      if (fc == NULL
		  || fc[0] == '\0'
		  || (strcmp (fc, "-1") == 0))
		{
		  newIndex->fields[x] = xstrdup ("0");
		}
	      else
		{
		  time_t t = get_any_date (fc);
		  asprintf (&(newIndex->fields[x]), "%d", (int) t);
		}
	    }
	  else
	    {
	      char *fcCopy;

	      if (fc == NULL)
		{
		  fcCopy = xstrdup ("");
		}
	      else
		{
		  fcCopy = xstrdup (fc);
		}


	      if (fieldDefForIndex (field)->nospaces)
		{

		  char *p = strchr (fcCopy, ' ');
		  if (p != NULL)
		    {
		      *p = '\0';
		    }
		}
	      newIndex->fields[x] = fcCopy;
	    }
	}
    }
}
