draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *clip,int pri)
{
	int offs,my,mx,code,code2,fx,fy,cgy=0,cgx,colour,i;


	for (offs=(HuC6270_registers[19]<<1)+0x200-8; offs>=(HuC6270_registers[19]<<1); offs-=8)
	{
		if ((HuC6270_vram[offs+7]&0x80) && !pri) continue;
		if (!(HuC6270_vram[offs+7]&0x80) && pri) continue;

		code=HuC6270_vram[offs+5] + (HuC6270_vram[offs+4]<<8);
		code=code>>1;

		my=HuC6270_vram[offs+1] + (HuC6270_vram[offs+0]<<8);
		mx=HuC6270_vram[offs+3] + (HuC6270_vram[offs+2]<<8);

		mx-=32;
		my-=57;

		fx=HuC6270_vram[offs+6]&0x8;
		fy=HuC6270_vram[offs+6]&0x80;
		cgx=HuC6270_vram[offs+6]&1;
		colour=HuC6270_vram[offs+7]&0xf;

		switch ((HuC6270_vram[offs+6]>>4)&3) {
		case 0: cgy=1; break;
		case 1: cgy=2; break;
		case 2: cgy=0; break;
		case 3: cgy=4; break;
		}

		if (cgx && cgy==2) code=code&0x3fc;

		if (fx && cgx) {code2=code; code++;}
		else code2=code+1;

		for (i=0; i<cgy; i++) {
			drawgfx(bitmap,Machine->gfx[1],
				code,
				colour,
				fx,fy,
				mx,my,
				clip,TRANSPARENCY_PEN,0);

			if (cgx)
				drawgfx(bitmap,Machine->gfx[1],
						code2,
						colour,
						fx,fy,
						mx+16,my,
						clip,TRANSPARENCY_PEN,0);
			my+=16;

			code+=2;
			code2+=2;

		}
	}

}
