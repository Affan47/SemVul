IsCornerExtremum(int xdir, int *contourends, BasePoint *bp, int p) {
    int PrevPoint = PrevOnContour(contourends, p);
    int NextPoint = NextOnContour(contourends, p);

return xdir?
    ((bp[PrevPoint].x > bp[p].x && bp[NextPoint].x > bp[p].x) ||
     (bp[PrevPoint].x < bp[p].x && bp[NextPoint].x < bp[p].x)):
    ((bp[PrevPoint].y > bp[p].y && bp[NextPoint].y > bp[p].y) ||
     (bp[PrevPoint].y < bp[p].y && bp[NextPoint].y < bp[p].y));
}
