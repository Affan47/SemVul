bhpl_16_nd(struct mame_bitmap *b,int x,int y,int w, UINT32* pens)
{
	UINT16* lineadr = &(((UINT16*)b->line[y])[x]);
	while(w-->0)
	{
		*lineadr++ = (UINT16)(*pens);
		pens++;
	}
}
