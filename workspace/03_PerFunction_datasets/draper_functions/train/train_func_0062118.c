draw_action_volume (GsdOsdDrawContext *ctx,
                    cairo_t           *cr)
{
        int window_width;
        int window_height;
        double icon_box_width;
        double icon_box_height;
        double icon_box_x0;
        double icon_box_y0;
        double volume_box_x0;
        double volume_box_y0;
        double volume_box_width;
        double volume_box_height;
        gboolean res;

	window_width = window_height = ctx->size;

        icon_box_width = round (window_width * ICON_SCALE);
        icon_box_height = round (window_height * ICON_SCALE);
        volume_box_width = icon_box_width;
        volume_box_height = round (window_height * 0.05);

        icon_box_x0 = round ((window_width - icon_box_width) / 2);
        icon_box_y0 = round ((window_height - icon_box_height - volume_box_height) / 2 - volume_box_height);
        volume_box_x0 = round (icon_box_x0);
        volume_box_y0 = round (icon_box_height + icon_box_y0) + volume_box_height;

#if 0
        g_message ("icon box: w=%f h=%f _x0=%f _y0=%f",
                   icon_box_width,
                   icon_box_height,
                   icon_box_x0,
                   icon_box_y0);
        g_message ("volume box: w=%f h=%f _x0=%f _y0=%f",
                   volume_box_width,
                   volume_box_height,
                   volume_box_x0,
                   volume_box_y0);
#endif

        res = render_speaker (ctx,
                              cr,
                              icon_box_x0, icon_box_y0,
                              icon_box_width, icon_box_height);
        if (! res) {
                double speaker_width;
                double speaker_height;
                double speaker_cx;
                double speaker_cy;

                speaker_width = icon_box_width * 0.5;
                speaker_height = icon_box_height * 0.75;
                speaker_cx = icon_box_x0 + speaker_width / 2;
                speaker_cy = icon_box_y0 + speaker_height / 2;

#if 0
                g_message ("speaker box: w=%f h=%f cx=%f cy=%f",
                           speaker_width,
                           speaker_height,
                           speaker_cx,
                           speaker_cy);
#endif


                draw_speaker (cr, speaker_cx, speaker_cy, speaker_width, speaker_height);

                if (!ctx->volume_muted) {

                        double wave_x0;
                        double wave_y0;
                        double wave_radius;

                        wave_x0 = window_width / 2;
                        wave_y0 = speaker_cy;
                        wave_radius = icon_box_width / 2;

                        draw_waves (cr, wave_x0, wave_y0, wave_radius, ctx->volume_level);
                } else {

                        double cross_x0;
                        double cross_y0;
                        double cross_size;

                        cross_size = speaker_width * 3 / 4;
                        cross_x0 = icon_box_x0 + icon_box_width - cross_size;
                        cross_y0 = speaker_cy;

                        draw_cross (cr, cross_x0, cross_y0, cross_size);
                }
        }


        draw_volume_boxes (ctx,
                           cr,
                           (double) ctx->volume_level / 100.0,
                           volume_box_x0,
                           volume_box_y0,
                           volume_box_width,
                           volume_box_height);
}
