draw(
	float x,
	float y,
	CL_GraphicContext *gc)
{
	if(impl->finished == false || impl->show_on_finish != show_blank)
	{

		CL_Sprite_Generic::SpriteFrame &frame = impl->frames[impl->current_frame];

		if (gc == 0) gc = CL_Display::get_current_window()->get_gc();

		static CL_Surface_DrawParams2 params2;

		params2.destX = x;
		params2.destY = y;
		params2.srcX = frame.position.left;
		params2.srcY = frame.position.top;
		params2.srcWidth = frame.position.get_width();
		params2.srcHeight = frame.position.get_height();
		params2.destZ = 0.0;
		params2.red = impl->red;
		params2.green = impl->green;
		params2.blue = impl->blue;
		params2.alpha = impl->alpha;
		params2.blend_src = impl->blend_src;
		params2.blend_dest = impl->blend_dest;
		params2.blendfunc_src_alpha  = impl->blendfunc_src_alpha;
		params2.blendfunc_dest_alpha = impl->blendfunc_dest_alpha;
		params2.scale_x = impl->scale_x;
		params2.scale_y = impl->scale_y;
		params2.translate_origin = impl->translation_origin;
		params2.translate_x = impl->translation_hotspot.x + frame.offset.x;
		params2.translate_y = impl->translation_hotspot.y + frame.offset.y;
		params2.rotate_angle = impl->angle - impl->base_angle;
		params2.rotate_pitch = impl->angle_pitch;
		params2.rotate_yaw = impl->angle_yaw;
		params2.rotate_origin = impl->rotation_origin;
		params2.rotate_x = impl->rotation_hotspot.x + frame.offset.x;
		params2.rotate_y = impl->rotation_hotspot.y + frame.offset.y;

		frame.surface.draw(params2,
                                   gc);
	}
}
