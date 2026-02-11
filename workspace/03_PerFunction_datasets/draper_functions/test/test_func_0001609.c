G_adjust_window_to_box(const struct Cell_head *src,
			   struct Cell_head *dst, int rows, int cols)
{
    double ew, ns;

    G_copy((char *)dst, (char *)src, sizeof(*dst));


    ns = (src->ns_res * src->rows) / rows;
    ew = (src->ew_res * src->cols) / cols;


    if (ns > ew)
	ew = ns;
    else
	ns = ew;

    dst->ns_res = ns;
    dst->ew_res = ew;


    dst->rows = (dst->north - dst->south) / dst->ns_res;
    dst->cols = (dst->east - dst->west) / dst->ew_res;

    return 0;
}
