write_png_size_string (char *s, PlotType ptype,
				   GptFlags flags, double scale)
{
    int w = GP_WIDTH, h = GP_HEIGHT;

    if (flags & GPT_LETTERBOX) {

	w = GP_LB_WIDTH;
	h = GP_LB_HEIGHT;
    } else if (flags & GPT_XL) {

	w = GP_XL_WIDTH;
	h = GP_XL_HEIGHT;
    } else if (flags & GPT_XXL) {

	w = GP_XXL_WIDTH;
	h = GP_XXL_HEIGHT;
    } else if (ptype == PLOT_ROOTS || ptype == PLOT_QQ) {

	w = h = GP_SQ_SIZE;
    }

    if (scale != 1.0) {
	plot_get_scaled_dimensions(&w, &h, scale);
    }

    *s = '\0';

    sprintf(s, " size %d,%d", w, h);
}
