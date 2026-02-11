psikyosh_drawbackground( struct mame_bitmap *bitmap, const struct rectangle *cliprect, UINT8 req_pri )
{
	int i, layer[3] = {0, 1, 2}, bg_pri[3];


	for (i=0; i<=2; i++)
	{
		if ( BG_TYPE(i) == BG_NORMAL_ALT )
			bg_pri[i]  = ((psikyosh_bgram[0x1ff0/4 + (i*0x04)/4] & 0xff000000) >> 24);
		else if ( (BG_TYPE(i) == BG_NORMAL) )
			bg_pri[i]  = ((psikyosh_bgram[0x17f0/4 + (i*0x04)/4] & 0xff000000) >> 24);
		else
			bg_pri[i] = (psikyosh_bgram[(BG_TYPE(i)*0x800)/4 + 0x400/4 - 0x4000/4] & 0xff000000) >> 24;
	}

#if 0
#ifdef MAME_DEBUG
	usrintf_showmessage	("Pri %d=%02x-%s %d=%02x-%s %d=%02x-%s",
		layer[0], BG_TYPE(layer[0]), BG_LAYER_ENABLE(layer[0])?"y":"n",
		layer[1], BG_TYPE(layer[1]), BG_LAYER_ENABLE(layer[1])?"y":"n",
		layer[2], BG_TYPE(layer[2]), BG_LAYER_ENABLE(layer[2])?"y":"n");
#endif
#endif


	for(i=0; i<=2; i++)
	{
		if(bg_pri[i] == req_pri)
			if ( BG_LAYER_ENABLE(layer[i]) )
			{
				if( BG_TYPE(layer[i]) == BG_NORMAL ||
					BG_TYPE(layer[i]) == BG_NORMAL_ALT )
				{
					psikyosh_drawbglayer(layer[i], bitmap, cliprect);
				}
				else if( BG_TYPE(layer[i]) == BG_SCROLL_0C ||
					BG_TYPE(layer[i]) == BG_SCROLL_0D )
				{
					psikyosh_drawbglayertext(layer[i], bitmap, cliprect);
				}
				else if( BG_TYPE(layer[i]) >= BG_SCROLL_ZOOM && BG_TYPE(layer[i]) <= 0x1f)
				{
					psikyosh_drawbglayerscroll(layer[i], bitmap, cliprect);
				}
				else
				{
					usrintf_showmessage	("Unknown layer type %02x", BG_TYPE(layer[i]));
					break;
				}
			}
	}
}
