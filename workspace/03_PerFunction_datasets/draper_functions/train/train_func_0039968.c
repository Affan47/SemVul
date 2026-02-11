CreateCubeAnalysis(moverecord * pmr, const matchstate * pms, int did_double, int did_take, int hist)
{
    doubletype dt = DoubleType(pms->fDoubled, pms->fMove, pms->fTurn);
    cubehintdata *pchd = g_new0(cubehintdata, 1);

    GtkWidget *pw, *pwhb, *pwx;

    pchd->pmr = pmr;
    pchd->ms = *pms;
    pchd->did_double = did_double;
    pchd->did_take = did_take;
    pchd->hist = hist;
    pchd->pw = pw = gtk_hbox_new(FALSE, 2);
    switch (pmr->mt) {

    case MOVE_NORMAL:
    case MOVE_SETDICE:


    case MOVE_SETCUBEPOS:
    case MOVE_SETCUBEVAL:


    case MOVE_DOUBLE:
        if (dt == DT_NORMAL)
            pchd->pwFrame = CubeAnalysis(pchd);
        else if (dt == DT_BEAVER)
            pchd->pwFrame = TakeAnalysis(pchd);
        break;
    case MOVE_TAKE:
    case MOVE_DROP:
        pchd->pwFrame = TakeAnalysis(pchd);
        break;
    default:
        g_assert_not_reached();
        break;

    }

    if (!pchd->pwFrame)
        return NULL;

    gtk_box_pack_start(GTK_BOX(pw), pchd->pwFrame, FALSE, FALSE, 0);

    pwx = gtk_vbox_new(FALSE, 0);

    gtk_box_pack_start(GTK_BOX(pwx), pw, FALSE, FALSE, 0);

    pwhb = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pwhb), CreateCubeAnalysisTools(pchd), FALSE, FALSE, 8);

    gtk_box_pack_start(GTK_BOX(pwx), pwhb, FALSE, FALSE, 0);


    g_object_set_data_full(G_OBJECT(pw), "cubehintdata", pchd, g_free);

    return pwx;

}
