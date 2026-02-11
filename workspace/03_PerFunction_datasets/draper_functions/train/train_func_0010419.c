setRequired(const PosTileIdx& ti)
{
	int tgi = tileGroupIdx(ti);
	if (tilegroups[tgi] == NULL)
		tilegroups[tgi] = new TileGroup;
	bool prevset = tilegroups[tgi]->setRequired(ti);
	if (!prevset)
		reqcount++;
	return prevset;
}
