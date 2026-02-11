lib3ds_math_ease(float fp, float fc, float fn, float ease_from, float ease_to) {
    double s, step;
    double tofrom;
    double a;

    s = step = (float)(fc - fp) / (fn - fp);
    tofrom = ease_to + ease_from;
    if (tofrom != 0.0) {
        if (tofrom > 1.0) {
            ease_to = (float)(ease_to / tofrom);
            ease_from = (float)(ease_from / tofrom);
        }
        a = 1.0 / (2.0 - (ease_to + ease_from));

        if (step < ease_from) s = a / ease_from * step * step;
        else {
            if ((1.0 - ease_to) <= step) {
                step = 1.0 - step;
                s = 1.0 - a / ease_to * step * step;
            } else {
                s = ((2.0 * step) - ease_from) * a;
            }
        }
    }
    return((float)s);
}
