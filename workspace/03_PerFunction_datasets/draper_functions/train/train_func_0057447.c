op_formatexpr(oap)
    oparg_T	*oap;
{
# ifdef FEAT_VISUAL
    if (oap->is_VIsual)

	redraw_curbuf_later(INVERTED);
# endif

    if (fex_format(oap->start.lnum, oap->line_count, NUL) != 0)


	op_format(oap, FALSE);
}
