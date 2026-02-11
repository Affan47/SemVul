next_step (int *x, int *y, int *dir, unsigned long long *got, int *ttl)
{
    int xx = *x, yy = *y;

#ifdef DEBUG
    printf ("Step %d: (%d,%d), dir = %d, ttl = %d, score = %d\n", step++, 1 + *x, 1 + *y, *dir, *ttl, *got);
#endif

    (*ttl)--;
    if (*ttl <= 0)
        return;
    xx += inc_x[*dir];
    yy += inc_y[*dir];

#ifdef DEBUG
    show_field (*x, *y, xx, yy, *dir, *got, *ttl);
#endif


    if (bumps[xx][yy]) {
        *ttl -= costs[xx][yy];
        if (*ttl > 0)
            *got += values[xx][yy];
        *dir = rotate [*dir];
#ifdef DEBUG
        printf ("Hit bump at %d,%d. New ttl = %d, dir = %d, score = %d\n", xx+1, yy+1, *ttl, *dir, *got);
#endif
        return;
    }

#ifdef DEBUG
    printf ("Don't hit anything, new coord (%d,%d)\n", xx+1, yy+1);
#endif
    *x = xx;
    *y = yy;
}
