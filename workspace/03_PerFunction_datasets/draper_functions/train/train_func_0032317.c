gst_draw_rle_line (GstDvdSubDec * dec, guchar * buffer, RLE_state * state)
{
  gint length, colourid;
  guint code;
  gint x, right;
  guchar *target;

  target = state->target;

  x = dec->left;
  right = dec->right + 1;

  while (x < right) {
    gboolean in_hl;
    const Color_val *colour_entry;

    code = gst_get_rle_code (buffer, state);
    length = code >> 2;
    colourid = code & 3;
    if (dec->use_ARGB)
      colour_entry = dec->palette_cache_rgb + colourid;
    else
      colour_entry = dec->palette_cache_yuv + colourid;


    if (length == 0 || x + length > right)
      length = right - x;


    in_hl = ((x <= state->hl_right) && (x + length) >= state->hl_left);
    if (in_hl) {
      gint run;


      if (x <= state->hl_left) {
        run = MIN (length, state->hl_left - x + 1);

        DRAW_RUN (target, run, colour_entry);
        length -= run;
        x += run;
      }


      if (x <= state->hl_right) {
        const Color_val *hl_colour;
        if (dec->use_ARGB)
          hl_colour = dec->hl_palette_cache_rgb + colourid;
        else
          hl_colour = dec->hl_palette_cache_yuv + colourid;

        run = MIN (length, state->hl_right - x + 1);

        DRAW_RUN (target, run, hl_colour);
        length -= run;
        x += run;
      }
    }


    if (length > 0) {
      DRAW_RUN (target, length, colour_entry);
      x += length;
    }
  }
}
