draw_subpixel(
					  const CL_Rectf &src,
					  const CL_Rectf &dest,
					  CL_GraphicContext *gc)
{
	static CL_Surface_DrawParams2 params2;
	params2.srcX = int(src.left);
	params2.srcY = int(src.top);
	params2.srcWidth = int(src.get_width());
	params2.srcHeight = int(src.get_height());
	params2.destX = dest.left;
	params2.destY = dest.top;
	params2.destZ = 0.0;
	params2.red = impl->red;
	params2.green = impl->green;
	params2.blue = impl->blue;
	params2.alpha = impl->alpha;

	params2.blend_src = impl->blend_src;
	params2.blend_dest = impl->blend_dest;
	params2.blendfunc_src_alpha = impl->blendfunc_src_alpha;
	params2.blendfunc_dest_alpha = impl->blendfunc_dest_alpha;

	params2.scale_x = dest.get_width()/float(src.get_width());
	params2.scale_y = dest.get_height()/float(src.get_height());
	params2.translate_origin = impl->translation_origin;
	params2.translate_x = int(impl->translation_hotspot.x);
	params2.translate_y = int(impl->translation_hotspot.y);
	params2.rotate_angle = impl->angle;
	params2.rotate_pitch = impl->angle_pitch;
	params2.rotate_yaw = impl->angle_yaw;
	params2.rotate_origin = impl->rotation_origin;
	params2.rotate_x = int(impl->rotation_hotspot.x);
	params2.rotate_y = int(impl->rotation_hotspot.y);
	params2.sub_pixel_accuracy = true;

	draw(params2, gc);
}
