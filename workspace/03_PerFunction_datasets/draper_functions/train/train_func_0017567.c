nis_servstate (const nis_server *serv, const nis_tag *tags,
	       const int numtags, nis_tag **result)
{
  nis_taglist taglist;
  nis_taglist tagres;

  *result = 0;
  tagres.tags.tags_len = 0;
  tagres.tags.tags_val = NULL;
  taglist.tags.tags_len = numtags;
  taglist.tags.tags_val = (nis_tag *) tags;

  if (serv == NULL)
    return NIS_BADOBJECT;

  if (__do_niscall2 (serv, 1, NIS_SERVSTATE, (xdrproc_t) _xdr_nis_taglist,
		     (caddr_t) &taglist, (xdrproc_t) _xdr_nis_taglist,
		     (caddr_t) &tagres, 0, NULL) != NIS_SUCCESS)
    return NIS_RPCERROR;

  *result = tagres.tags.tags_val;

  return NIS_SUCCESS;
}
