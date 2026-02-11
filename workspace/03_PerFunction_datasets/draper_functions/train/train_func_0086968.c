CalcShape(Shape* s) {
    TElement* ltray, *rtray, *btray, *ttray;

    hnodes->FindElements(tray, ltray, rtray);
    vnodes->FindElements(tray, btray, ttray);

    if (ltray != nil && lmagic != nil) {
        ltray->combinable = rtray->combinable = false;
        Solve(hnodes, lmagic, rmagic, 0, s->width, s->hshrink, s->hstretch);
        ltray->combinable = rtray->combinable = true;
    }

    if (btray != nil && bmagic != nil) {
        btray->combinable = ttray->combinable = false;
        Solve(vnodes, bmagic, tmagic, 0, s->height, s->vshrink, s->vstretch);
        btray->combinable = ttray->combinable = true;
    }
}
