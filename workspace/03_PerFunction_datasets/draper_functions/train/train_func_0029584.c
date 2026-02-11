pac_chasing (pacmangamestruct * pp, pacmanstruct * p)
{
    int posdirs[DIRVECS], nrdirs, i, highest = -(1 << 16),
        score, dir = 0, worst = 0;
    int vx = 0, vy = 0;

    nrdirs = pac_get_posdirs (pp, p, posdirs);


    for (i = 0; i < DIRVECS; i++) {
        if (posdirs[i] == 0)
            continue;
        score = vx * dirvecs[i].dx + vy * dirvecs[i].dy;
        if (score < highest) {
            worst = i;
            highest = score;
        }
        dir = i;
    }
    nrdirs--;
    posdirs[worst] = 0;


    for (i = 0; i < DIRVECS; i++)
        if (posdirs[i] != 0)
            dir = i;

    {
        long lvx = vx;
        long lvy = vy;
        pac_dot_vec (pp, p, &lvx, &lvy);
        vx = lvx;
        vy = lvy;
    }

    if (vx != NOWHERE && vy != NOWHERE && pac_check_trace (p, vx, vy) > 0) {
        p->roundscore++;
        if (p->roundscore >= 12) {
            p->roundscore = 0;
            p->aistate = ps_random;
            pacman_clear_trace (p);
        }
    }
    else
        p->roundscore = 0;


    p->nextrow = p->row + dirvecs[dir].dy;
    p->nextcol = p->col + dirvecs[dir].dx;
    p->lastbox = dir;
}
