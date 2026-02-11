HPDF_Page_Arc  (HPDF_Page    page,
                HPDF_REAL    x,
                HPDF_REAL    y,
                HPDF_REAL    ray,
                HPDF_REAL    ang1,
                HPDF_REAL    ang2)
{
    HPDF_BOOL cont_flg = HPDF_FALSE;

    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_PATH_OBJECT);

    HPDF_PTRACE ((" HPDF_Page_Arc\n"));

    if (fabs(ang2 - ang1) >= 360)
        HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (ret != HPDF_OK)
        return ret;

    while (ang1 < 0 || ang2 < 0) {
        ang1 = ang1 + 360;
        ang2 = ang2 + 360;
    }


    for (;;) {
        if (fabs(ang2 - ang1) <= 90)
            return InternalArc (page, x, y, ray, ang1, ang2, cont_flg);
        else {
	    HPDF_REAL tmp_ang = (ang2 > ang1 ? ang1 + 90 : ang1 - 90);

            if ((ret = InternalArc (page, x, y, ray, ang1, tmp_ang, cont_flg))
                    != HPDF_OK)
                return ret;

            ang1 = tmp_ang;
        }

        if (fabs(ang1 - ang2) < 0.1)
            break;

        cont_flg = HPDF_TRUE;
    }

    return HPDF_OK;
}
