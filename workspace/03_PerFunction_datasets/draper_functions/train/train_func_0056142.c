plot_polygon(double *xf, double *yf, int n)
{
    switch (render) {
    case RENDER_GPP:
	G_plot_polygon(xf, yf, n);
	break;
    case RENDER_DP:
	D_polygon(xf, yf, n);
	break;
    case RENDER_DPC:
	D_polygon_clip(xf, yf, n);
	break;
    case RENDER_DPL:
	D_polygon_cull(xf, yf, n);
	break;
    case RENDER_RPA:
	local_plot_poly(xf, yf, n, RENDER_POLYGON);
	break;
    default:
	G_plot_polygon(xf, yf, n);
	break;
    }
}
