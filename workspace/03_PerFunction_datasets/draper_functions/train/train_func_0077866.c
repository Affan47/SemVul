dsio_load(Ds *ds)
{
  int ch, rc;

  ds_errmsg = NULL;
  if (ds == NULL || ds->io == NULL) {
	ds_errmsg = "no input source is configured";
	return(-1);
  }

  if (ds->len_limit > 0 && ds->len == ds->len_limit) {
	ds_errmsg = "max limit exceeded";
	return(-1);
  }

  if ((rc = dsio_eof(ds)) == -1)
    return(-1);

  if (rc == 1)
    return(0);

  rc = 1;
  if (ds->io->got_peeked_char) {
    ch = ds->io->peeked_char & 0377;
	if (ds_appendc(ds, ch) == -1)
	  return(-1);
	ds->io->got_peeked_char = 0;
  }

  if (ds->io->fp != NULL) {
	while (dsio_eof(ds) == 0) {
	  char ach;

	  if (fread(&ach, 1, 1, ds->io->fp) != 1)
		break;
	  if (ds_appendc(ds, (int) ach) == -1)
		return(-1);
	  if (ds->io->have_length)
		ds->io->rem--;
	}
	if (ferror(ds->io->fp))
	  return(-1);
  }
  else {
	if (ds->io->length > ds->io->rem)
	  return(-1);
	if (ds_copyb(ds, ds->io->ptr, ds->io->length, ds->len) == NULL)
	  return(-1);
	ds->io->ptr += ds->io->length;
	ds->io->rem -= ds->io->length;
  }

  return(1);
}
