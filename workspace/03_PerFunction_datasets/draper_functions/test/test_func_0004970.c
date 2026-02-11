drawBlips(int blip_type, int bright, int distort)
{
	blip *b = NULL;
	blip *blip_head;
	vec3d pos;
	float alpha;

	Assert((blip_type >= 0) && (blip_type < MAX_BLIP_TYPES));


	gr_set_font(FONT1);

	if(bright) {
		blip_head = &Blip_bright_list[blip_type];
	} else {
		blip_head = &Blip_dim_list[blip_type];
	}

	float scale = 1.0f;


	for (b = GET_FIRST(blip_head); b != END_OF_LIST(blip_head); b = GET_NEXT(b))
	{
		plotBlip(b, &pos, &alpha);

		gr_set_color_fast(b->blip_color);

		scale = 1.0f;


		if (b->flags & BLIP_CURRENT_TARGET)
		{
			if (radar_target_id_flags & RTIF_PULSATE) {
				scale *= 1.3f + (sinf(10 * f2fl(Missiontime)) * 0.3f);
			}
			if (radar_target_id_flags & RTIF_BLINK) {
				if (Missiontime & 8192)
					continue;
			}
			if (radar_target_id_flags & RTIF_ENLARGE) {
				scale *= 1.3f;
			}

			alpha = 1.0;
			b->rad = Radar_blip_radius_target;
			drawContact(&pos, -1, target_brackets, b->dist, alpha, scale);
		}
		else {
			b->rad = Radar_blip_radius_normal;
		}


		if (distort) {
			blipDrawDistorted(b, &pos, alpha);
		} else {
			if (b->flags & BLIP_DRAW_DISTORTED) {
				blipDrawFlicker(b, &pos, alpha);
			} else if (b->radar_image_2d >= 0 || b->radar_color_image_2d >= 0) {
				drawContact(&pos, b->radar_image_2d, b->radar_color_image_2d, b->dist, alpha, scale);
			} else {
				drawContact(&pos, -1, unknown_contact_icon, b->dist, alpha, scale);
			}
		}
	}
}
