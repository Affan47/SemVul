tpg_fill_plane_buffer(struct tpg_data *tpg, v4l2_std_id std,
			   unsigned p, u8 *vbuf)
{
	struct tpg_draw_params params;
	unsigned factor = V4L2_FIELD_HAS_T_OR_B(tpg->field) ? 2 : 1;


	unsigned int_part = (tpg->crop.height / factor) / tpg->compose.height;
	unsigned fract_part = (tpg->crop.height / factor) % tpg->compose.height;
	unsigned src_y = 0;
	unsigned error = 0;
	unsigned h;

	tpg_recalc(tpg);

	params.is_tv = std;
	params.is_60hz = std & V4L2_STD_525_60;
	params.twopixsize = tpg->twopixelsize[p];
	params.img_width = tpg_hdiv(tpg, p, tpg->compose.width);
	params.stride = tpg->bytesperline[p];
	params.hmax = (tpg->compose.height * tpg->perc_fill) / 100;

	tpg_fill_params_pattern(tpg, p, &params);
	tpg_fill_params_extras(tpg, p, &params);

	vbuf += tpg_hdiv(tpg, p, tpg->compose.left);

	for (h = 0; h < tpg->compose.height; h++) {
		unsigned buf_line;

		params.frame_line = tpg_calc_frameline(tpg, src_y, tpg->field);
		params.frame_line_next = params.frame_line;
		buf_line = tpg_calc_buffer_line(tpg, h, tpg->field);
		src_y += int_part;
		error += fract_part;
		if (error >= tpg->compose.height) {
			error -= tpg->compose.height;
			src_y++;
		}


		if (tpg_g_interleaved(tpg))
			p = tpg_g_interleaved_plane(tpg, buf_line);

		if (tpg->vdownsampling[p] > 1) {


			if (tpg->field == V4L2_FIELD_SEQ_BT ||
			    tpg->field == V4L2_FIELD_SEQ_TB) {
				unsigned next_src_y = src_y;

				if ((h & 3) >= 2)
					continue;
				next_src_y += int_part;
				if (error + fract_part >= tpg->compose.height)
					next_src_y++;
				params.frame_line_next =
					tpg_calc_frameline(tpg, next_src_y, tpg->field);
			} else {
				if (h & 1)
					continue;
				params.frame_line_next =
					tpg_calc_frameline(tpg, src_y, tpg->field);
			}

			buf_line /= tpg->vdownsampling[p];
		}
		tpg_fill_plane_pattern(tpg, &params, p, h,
				vbuf + buf_line * params.stride);
		tpg_fill_plane_extras(tpg, &params, p, h,
				vbuf + buf_line * params.stride);
	}
}
