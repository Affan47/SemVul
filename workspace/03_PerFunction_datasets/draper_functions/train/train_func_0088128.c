_clutter_id_to_color (guint         id_,
                      ClutterColor *col)
{
  ClutterMainContext *ctx;
  gint red, green, blue;

  ctx = _clutter_context_get_default ();

  if (ctx->fb_g_mask == 0)
    {

      cogl_get_bitmasks (&ctx->fb_r_mask,
			 &ctx->fb_g_mask,
			 &ctx->fb_b_mask, NULL);

      ctx->fb_r_mask_used = ctx->fb_r_mask;
      ctx->fb_g_mask_used = ctx->fb_g_mask;
      ctx->fb_b_mask_used = ctx->fb_b_mask;


      if (clutter_use_fuzzy_picking)
	{
	  ctx->fb_r_mask_used--;
	  ctx->fb_g_mask_used--;
	  ctx->fb_b_mask_used--;
	}
    }


  red   = (id_ >> (ctx->fb_g_mask_used+ctx->fb_b_mask_used))
        & (0xff >> (8-ctx->fb_r_mask_used));
  green = (id_ >> ctx->fb_b_mask_used)
        & (0xff >> (8-ctx->fb_g_mask_used));
  blue  = (id_)
        & (0xff >> (8-ctx->fb_b_mask_used));


  if (ctx->fb_r_mask_used != ctx->fb_r_mask)
    red = red * 2;
  if (ctx->fb_g_mask_used != ctx->fb_g_mask)
    green = green * 2;
  if (ctx->fb_b_mask_used != ctx->fb_b_mask)
    blue  = blue  * 2;


  red   = (red   << (8 - ctx->fb_r_mask)) | (0x7f >> (ctx->fb_r_mask_used));
  green = (green << (8 - ctx->fb_g_mask)) | (0x7f >> (ctx->fb_g_mask_used));
  blue  = (blue  << (8 - ctx->fb_b_mask)) | (0x7f >> (ctx->fb_b_mask_used));

  col->red   = red;
  col->green = green;
  col->blue  = blue;
  col->alpha = 0xff;


  if (G_UNLIKELY (clutter_pick_debug_flags & CLUTTER_DEBUG_DUMP_PICK_BUFFERS))
    {
      col->red   = (col->red << 4)   | (col->red >> 4);
      col->green = (col->green << 4) | (col->green >> 4);
      col->blue  = (col->blue << 4)  | (col->blue >> 4);
    }
}
