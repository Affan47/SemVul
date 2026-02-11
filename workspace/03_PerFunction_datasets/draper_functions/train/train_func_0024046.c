set_net_supported(int l)
{
	Atom *supported;
	int i, k = 0;

	supported = (Atom *)safemalloc(l*sizeof(Atom));
	for(i=0; i < NUMBER_OF_ATOM_LISTS; i++)
	{
		ewmh_atom *list = atom_list[i].list;
		while(list->name != NULL)
		{
			supported[k++] = list->atom;
			list++;
		}
	}

	ewmh_ChangeProperty(
		Scr.Root, "_NET_SUPPORTED", EWMH_ATOM_LIST_FVWM_ROOT,
		(unsigned char *)supported, k);
	free(supported);

	return;
}
