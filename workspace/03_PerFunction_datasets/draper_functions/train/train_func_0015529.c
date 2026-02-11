sys16_sprite_shinobi( struct sys16_sprite_attributes *sprite, const UINT16 *source, int bJustGetColor ){


	extern int sys16_wwfix;
	UINT16 ypos = source[0];
	UINT16 width = source[2];
	int top = ypos&0xff;
	int bottom = ypos>>8;
	if( bottom == 0xff || width ==sys16_spritelist_end ) return 1;

	if( bottom !=0 && bottom > top ){
		UINT16 attributes = source[4];
		UINT16 zoomx = source[5]&0x3ff;
		UINT16 zoomy = (source[6]&0x3ff);
		if( zoomy==0 || source[6]==0xffff ) zoomy = zoomx;
		sprite->x = source[1] + sys16_sprxoffset;
		sprite->y = top;
		sprite->priority = (attributes>>6)&0x3;
		sprite->color = 1024/16 + (attributes&0x3f);
		sprite->screen_height = bottom-top;
		sprite->flags = SYS16_SPR_VISIBLE;
		if( width&0x100 ) sprite->flags |= SYS16_SPR_FLIPX;
#ifdef TRANSPARENT_SHADOWS
		if ((attributes&0x3f)==0x3f) sprite->flags|= SYS16_SPR_SHADOW;
#endif
		sprite->zoomx = zoomx;
		sprite->zoomy = zoomy;
		sprite->pitch = source[2]&0xff;
		sprite->gfx = ( source[3] + (sys16_obj_bank[(attributes>>8)&0xf]<<(16+sys16_wwfix)) ) << 1;
	}
	return 0;
}
