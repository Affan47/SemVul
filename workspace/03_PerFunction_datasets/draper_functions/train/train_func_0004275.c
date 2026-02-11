pick(Canvas*, const Allocation& a, int depth, Hit& h) {
    Coord x = h.left();
    Coord y = h.bottom();
    if (x >= a.left() && x < a.right() && y >= a.bottom() && y < a.top()) {
        h.target(depth, this, 0);
    }
}
