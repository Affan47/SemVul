find_by_index(int idx)
{
	struct idxmap *im;

	if (idxmap)
		for (im = idxmap[idx & 0xF]; im; im = im->next)
			if (im->index == idx)
				return im;
	return NULL;
}
