GParrow (Gwidget_t *widget, Gpoint_t gp1, Gpoint_t gp2, Ggattr_t *ap) {
    PIXpoint_t pp1, pp2, pa, pb, pd;
    double tangent;
    int l;

    pp1 = pdrawtopix (widget, gp1), pp2 = pdrawtopix (widget, gp2);
    pd.x = pp1.x - pp2.x, pd.y = pp1.y - pp2.y;
    if (pd.x == 0 && pd.y == 0)
        return 0;
    tangent = atan2 ((double) pd.y, (double) pd.x);
    if ((l = sqrt ((double) (pd.x * pd.x + pd.y * pd.y))) < 30)
        l = 30;
    pa.x = l * cos (tangent + M_PI / 7) + pp2.x;
    pa.y = l * sin (tangent + M_PI / 7) + pp2.y;
    pb.x = l * cos (tangent - M_PI / 7) + pp2.x;
    pb.y = l * sin (tangent - M_PI / 7) + pp2.y;
    setgattr (widget, ap);
    fprintf (
        FP, "%d %d %d %d LI\n",
        (int) pp2.x, (int) pp2.y, (int) pp1.x, (int) pp1.y
    );
    fprintf (
        FP, "%d %d %d %d LI\n",
        (int) pp2.x, (int) pp2.y, (int) pa.x, (int) pa.y
    );
    fprintf (
        FP, "%d %d %d %d LI\n",
        (int) pp2.x, (int) pp2.y, (int) pb.x, (int) pb.y
    );
    return 0;
}
