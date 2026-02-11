find_plci_by_ncci(capidrv_contr *card, u32 ncci)
{
	capidrv_plci *p;
	for (p = card->plci_list; p; p = p->next)
		if (p->plci == (ncci & 0xffff))
			return p;
	return NULL;
}
