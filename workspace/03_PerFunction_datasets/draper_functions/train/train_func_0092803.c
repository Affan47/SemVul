main(int argc, char *argv[])
{
    int p, x, y, val, cost, dir, ttl, wall_cost;
    unsigned long long score = 0, got;
    int i;

    scanf ("%d %d %d", &max_x, &max_y, &wall_cost);
    scanf ("%d", &p);

    max_x--;
    max_y--;


    for (i = 0; i <= max_x; i++) {
        bumps[i][0] = bumps[i][max_y] = 2;
        values[i][0] = values[i][max_y] = 0;
        costs[i][0] = costs[i][max_y] = wall_cost;
    }

    for (i = 0; i <= max_y; i++) {
        bumps[0][i] = bumps[max_x][i] = 2;
        values[0][i] = values[max_x][i] = 0;
        costs[0][i] = costs[max_x][i] = wall_cost;
    }

    if (p) {
        while (p--) {
            scanf ("%d %d %d %d", &x, &y, &val, &cost);
            x--;
            y--;
            bumps[x][y] = 1;
            values[x][y] = val;
            costs[x][y] = cost;
        }
    }

    while (scanf ("%d %d %d %d", &x, &y, &dir, &ttl) == 4) {
        got = 0;
        x--;
        y--;

#ifdef DEBUG
        printf ("\nNew ball @(%d,%d), dir = %d, ttl = %d\n", x+1, y+1, dir, ttl);
#endif

        while (ttl > 0) {
            next_step (&x, &y, &dir, &got, &ttl);
            if (ttl <= 0)
                break;
        }

        score += got;
        printf ("%llu\n", got);
    }

    printf ("%llu\n", score);
    return 0;
}
