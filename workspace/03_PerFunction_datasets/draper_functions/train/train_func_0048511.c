ndmda_fh_prepare (struct ndm_session *sess,
  int vers, int msg, int entry_size,
  unsigned n_item, unsigned total_size_of_items)
{
	struct ndm_data_agent *	da = &sess->data_acb;
	struct ndmfhheap *	fhh = &da->fhh;
	int			fhtype = (vers<<16) + msg;
	int			rc;

	rc = ndmfhh_prepare (fhh, fhtype, entry_size,
				n_item, total_size_of_items);

	if (rc == NDMFHH_RET_OK)
		return NDMFHH_RET_OK;

	ndmda_fh_flush (sess);

	rc = ndmfhh_prepare (fhh, fhtype, entry_size,
				n_item, total_size_of_items);

	return rc;
}
