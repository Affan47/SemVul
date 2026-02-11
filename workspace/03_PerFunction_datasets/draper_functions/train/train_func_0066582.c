sexp_key_construct (gcry_sexp_t *r_sexp,
		    ssh_key_type_spec_t key_spec, int secret,
		    const char *curve_name, gcry_mpi_t *mpis,
                    const char *comment)
{
  const char *key_identifier[] = { "public-key", "private-key" };
  gpg_error_t err;
  gcry_sexp_t sexp_new = NULL;
  void *formatbuf = NULL;
  void **arg_list = NULL;
  int arg_idx;
  estream_t format;
  const char *elems;
  size_t elems_n;
  unsigned int i, j;

  if (secret)
    elems = key_spec.elems_sexp_order;
  else
    elems = key_spec.elems_key_public;
  elems_n = strlen (elems);

  format = es_fopenmem (0, "a+b");
  if (!format)
    {
      err = gpg_error_from_syserror ();
      goto out;
    }


  arg_list = xtrymalloc (sizeof (*arg_list) * (2 + 1 + elems_n + 1 + 1));
  if (!arg_list)
    {
      err = gpg_error_from_syserror ();
      goto out;
    }
  arg_idx = 0;

  es_fputs ("(%s(%s", format);
  arg_list[arg_idx++] = &key_identifier[secret];
  arg_list[arg_idx++] = &key_spec.identifier;
  if (curve_name)
    {
      es_fputs ("(curve%s)", format);
      arg_list[arg_idx++] = &curve_name;
    }

  for (i = 0; i < elems_n; i++)
    {
      es_fprintf (format, "(%c%%m)", elems[i]);
      if (secret)
	{
	  for (j = 0; j < elems_n; j++)
	    if (key_spec.elems_key_secret[j] == elems[i])
	      break;
	}
      else
	j = i;
      arg_list[arg_idx++] = &mpis[j];
    }
  es_fputs (")(comment%s))", format);
  arg_list[arg_idx++] = &comment;
  arg_list[arg_idx] = NULL;

  es_putc (0, format);
  if (es_ferror (format))
    {
      err = gpg_error_from_syserror ();
      goto out;
    }
  if (es_fclose_snatch (format, &formatbuf, NULL))
    {
      err = gpg_error_from_syserror ();
      goto out;
    }
  format = NULL;

  err = gcry_sexp_build_array (&sexp_new, NULL, formatbuf, arg_list);
  if (err)
    goto out;

  *r_sexp = sexp_new;
  err = 0;

 out:
  es_fclose (format);
  xfree (arg_list);
  xfree (formatbuf);

  return err;
}
