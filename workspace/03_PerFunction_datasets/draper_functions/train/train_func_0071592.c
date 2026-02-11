adjustBorderRadii(BorderRadii &tl, BorderRadii &tr, BorderRadii &bl, BorderRadii &br, int w, int h) const
{


    const int horS = qMax(tl.horizontal + tr.horizontal, bl.horizontal + br.horizontal);
    const int verS = qMax(tl.vertical + bl.vertical, tr.vertical + br.vertical);

    qreal f = 1.0;
    if (horS > 0)
        f = qMin(f, w / qreal(horS));
    if (verS > 0)
        f = qMin(f, h / qreal(verS));

    if (f < 1.0) {
        tl.horizontal *= f;
        tr.horizontal *= f;
        bl.horizontal *= f;
        br.horizontal *= f;
        tl.vertical   *= f;
        tr.vertical   *= f;
        bl.vertical   *= f;
        br.vertical   *= f;
    }
}
