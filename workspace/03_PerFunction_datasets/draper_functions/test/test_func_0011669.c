blkid_probe_get_probername(blkid_probe pr)
{
	struct blkid_chain *chn = blkid_probe_get_chain(pr);

	if (chn && chn->idx >= 0 && chn->idx < chn->driver->nidinfos)
		return chn->driver->idinfos[chn->idx]->name;

	return NULL;
}
