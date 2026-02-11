splndrbt_update_clut(void)
{
	pen_t *colortable;
	int c;

	colortable = Machine->remapped_colortable;
	c = *bgcolor;

	switch(equites_id)
	{
		case 0x8511:
			colortable[0x114] = c;
		break;
	}
}
