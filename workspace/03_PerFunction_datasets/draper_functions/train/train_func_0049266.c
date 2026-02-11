find_dir_2(int x, int y) {
    int q;

    if (!y)
        q = -300*x;
    else
        q = x*100/y;
    if (y > 0) {
        if (q < -242)
            return 3;
        if (q < -41)
            return 2;
        if (q < 41)
            return 1;
        if (q < 242)
            return 8;
        return 7;
    }
    if (q < -242)
        return 7;
    if (q < -41)
        return 6;
    if (q < 41)
        return 5;
    if (q < 242)
        return 4;
    return 3;
}
