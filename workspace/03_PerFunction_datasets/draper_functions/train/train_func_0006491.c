clip_vline (const GS &gs, int &x, int &y, int &h) {
        const Rect &cliprect = gs.cliprect;

        if (x < cliprect.x || x >= cliprect.x + cliprect.w)
            return false;

        int d = y - cliprect.y;
        if (d < 0) {
            h += d;
            y = cliprect.y;
        }
        d = cliprect.y+cliprect.h - (y+h);
        if (d < 0)
            h += d;
        return h > 0;
    }
