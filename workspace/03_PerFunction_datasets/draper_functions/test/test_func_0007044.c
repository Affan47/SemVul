constrainSize(int &w, int &h, int flags)
{
    if (fSizeHints) {
        int const wMin(fSizeHints->min_width);
        int const hMin(fSizeHints->min_height);
        int const wMax(fSizeHints->max_width);
        int const hMax(fSizeHints->max_height);
        int const wBase(fSizeHints->base_width);
        int const hBase(fSizeHints->base_height);
        int const wInc(fSizeHints->width_inc);
        int const hInc(fSizeHints->height_inc);

        if (fSizeHints->flags & PAspect) {
            int const xMin(fSizeHints->min_aspect.x);
            int const yMin(fSizeHints->min_aspect.y);
            int const xMax(fSizeHints->max_aspect.x);
            int const yMax(fSizeHints->max_aspect.y);

            MSG(("aspect"));
            if (flags & csKeepX) {
                MSG(("keepX"));
            }
            if (flags & csKeepY) {
                MSG(("keepY"));
            }


            if (xMin * h > yMin * w) {
                if (flags & csKeepX) {
                    w = clamp(w, wMin, wMax);
                    h = w * yMin / xMin;
                    h = clamp(h, hMin, hMax);
                    w = h * xMin / yMin;
                } else {
                    h = clamp(h, hMin, hMax);
                    w = h * xMin / yMin;
                    w = clamp(w, wMin, wMax);
                    h = w * yMin / xMin;
                }
            }
            if (xMax * h < yMax * w) {
                if (flags & csKeepX) {
                    w = clamp(w, wMin, wMax);
                    h = w * yMax / xMax;
                    h = clamp(h, hMin, hMax);
                    w = h * xMax / yMax;
                } else {
                    h = clamp(h, hMin, hMax);
                    w = h * xMax / yMax;
                    w = clamp(w, wMin, wMax);
                    h = w * yMax / xMax;
                }
            }
        }

        h = clamp(h, hMin, hMax);
        w = clamp(w, wMin, wMax);

        if (flags & csRound) {
            w += wInc / 2; h += hInc / 2;
        }

        w-= max(0, w - wBase) % wInc;
        h-= max(0, h - hBase) % hInc;
    }

    if (w <= 0) w = 1;
    if (h <= 0) h = 1;
}
