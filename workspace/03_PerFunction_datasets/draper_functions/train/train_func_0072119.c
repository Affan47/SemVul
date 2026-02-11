Redraw(IntCoord x1, IntCoord y1, IntCoord x2, IntCoord y2) {
    register IntCoord r = xmax - right;
    register IntCoord t = ymax - top;

    if (x1 < left) {
        output->FillRect(canvas, 0, 0, left-1, t);
    }
    if (y1 < bottom) {
        output->FillRect(canvas, left, 0, xmax, bottom-1);
    }
    if (x2 > r) {
        output->FillRect(canvas, r+1, bottom, xmax, ymax);
    }
    if (y2 > t) {
        output->FillRect(canvas, 0, t+1, r, ymax);
    }
}
