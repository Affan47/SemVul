draw_edge(p_edge e, p_vertex v1, p_vertex v2)
{


    struct t_colorspec color = e->lp->pm3d_color;
    struct lp_style_type lptemp = *(e->lp);
    TBOOLEAN recolor = FALSE;
    TBOOLEAN arrow = (lptemp.p_type == PT_ARROWHEAD || lptemp.p_type == PT_BACKARROW);
    int varcolor;

    if (arrow && (e->style == PT_BACKARROW))
	varcolor = v2->real_z;
    else
	varcolor = v1->real_z;


    if (color.type == TC_RGB && color.lt == LT_COLORFROMCOLUMN) {
	recolor = TRUE;
	lptemp.pm3d_color.lt = varcolor;
    } else


    if (color.type == TC_RGB && e->style == LT_SINGLECOLOR) {
	recolor = TRUE;
    } else

    if (color.type == TC_RGB && e->lp == &border_lp) {
	lptemp.pm3d_color.lt = varcolor;
    } else


    if (lptemp.l_type == LT_COLORFROMCOLUMN) {
	recolor = TRUE;
	load_linetype(&lptemp, varcolor);
    } else


    if (arrow) {
	lptemp.p_type = e->style;
    } else


    if ((hiddenBacksideLinetypeOffset != 0)
    &&  (e->lp->pm3d_color.type != TC_Z)) {
	recolor = TRUE;
	load_linetype(&lptemp, e->style + 1);
	color = lptemp.pm3d_color;
    }


    else
	;

    if (recolor) {
	color = lptemp.pm3d_color;
	lptemp = *(e->lp);
	lptemp.pm3d_color = color;
	lptemp.use_palette = TRUE;
	if (arrow)
	    lptemp.p_type = e->style;
    }

    draw3d_line_unconditional(v1, v2, &lptemp, color);
    if (e->lp->pointflag) {
	draw_vertex(v1);
	draw_vertex(v2);
    }
}
