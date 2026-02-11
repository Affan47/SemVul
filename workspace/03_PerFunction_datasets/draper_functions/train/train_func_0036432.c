run_standardize(gx_device_run *rdev, int y, int h)
{
    int ye, iy;

    fit_fill_y(&rdev->md, y, h);
    fit_fill_h(&rdev->md, y, h);
    ye = y + h;
    if (y < rdev->smin) {
        if (ye > rdev->smax1)
            run_standardize(rdev, rdev->smax1, ye - rdev->smax1);
        if (ye < rdev->smin)
            ye = rdev->smin;
        rdev->smin = y;
    } else if (ye > rdev->smax1) {
        if (y > rdev->smax1)
            y = rdev->smax1;
        rdev->smax1 = ye;
    } else
        return 0;
    for (iy = y; iy < ye; ++iy)
        run_expand(rdev, iy);
    return 0;
}
