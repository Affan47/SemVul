deco16_print_debug_info(void)
{
	struct mame_bitmap *bitmap = Machine->scrbitmap;
	char buf[64];
	int j;

	if (keyboard_pressed(KEYCODE_O))
		return;

	if (deco16_pf12_control) {
		sprintf(buf,"%04X %04X %04X %04X",deco16_pf12_control[0],deco16_pf12_control[1],deco16_pf12_control[2],deco16_pf12_control[3]);
		for (j = 0;j< 16+3;j++)
			drawgfx(bitmap,Machine->uifont,buf[j],0,0,0,60+6*j,40,0,TRANSPARENCY_NONE,0);
		sprintf(buf,"%04X %04X %04X %04X",deco16_pf12_control[4],deco16_pf12_control[5],deco16_pf12_control[6],deco16_pf12_control[7]);
		for (j = 0;j< 16+3;j++)
			drawgfx(bitmap,Machine->uifont,buf[j],0,0,0,60+6*j,48,0,TRANSPARENCY_NONE,0);
	}
	if (deco16_pf34_control) {
		sprintf(buf,"%04X %04X %04X %04X",deco16_pf34_control[0],deco16_pf34_control[1],deco16_pf34_control[2],deco16_pf34_control[3]);
		for (j = 0;j< 16+3;j++)
			drawgfx(bitmap,Machine->uifont,buf[j],0,0,0,60+6*j,60,0,TRANSPARENCY_NONE,0);
		sprintf(buf,"%04X %04X %04X %04X",deco16_pf34_control[4],deco16_pf34_control[5],deco16_pf34_control[6],deco16_pf34_control[7]);
		for (j = 0;j< 16+3;j++)
			drawgfx(bitmap,Machine->uifont,buf[j],0,0,0,60+6*j,68,0,TRANSPARENCY_NONE,0);
	}
	sprintf(buf,"%04X",deco16_priority);
	for (j = 0;j< 4;j++)
		drawgfx(bitmap,Machine->uifont,buf[j],0,0,0,60+6*j,80,0,TRANSPARENCY_NONE,0);
}
