mooncrst_modify_spritecode(data8_t *spriteram,int *code,int *flipx,int *flipy,int offs)
{
	if (gfxbank[2] && ((*code & 0x30) == 0x20))
	{
		*code = (*code & 0x0f) | (gfxbank[0] << 4) | (gfxbank[1] << 5) | 0x40;
	}
}
