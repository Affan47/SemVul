free_pacman (Display * display, pacmangamestruct * pp)
{
    int dir, mouth, i, j, k;

    if (pp->ghosts != NULL) {
        free (pp->ghosts);
        pp->ghosts = (ghoststruct *) NULL;
    }
    if (pp->stippledGC != None) {
        XFreeGC (display, pp->stippledGC);
        pp->stippledGC = None;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < MAXGDIR; j++) {
            for (k = 0; k < MAXGWAG; k++) {
                if (pp->ghostPixmap[i][j][k] != None) {
                    XFreePixmap (display, pp->ghostPixmap[i][j][k]);
                    pp->ghostPixmap[i][j][k] = None;
                }
            }
        }
    }
    for (dir = 0; dir < 4; dir++)
        for (mouth = 0; mouth < MAXMOUTH; mouth++)
            if (pp->pacmanPixmap[dir][mouth] != None) {
                XFreePixmap (display, pp->pacmanPixmap[dir][mouth]);
                pp->pacmanPixmap[dir][mouth] = None;
            }
}
