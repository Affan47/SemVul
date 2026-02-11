set_apparxy(struct monst *mtmp)
{
    bool notseen, gotu;
    int disp, mx = mtmp->mux, my = mtmp->muy;


    if (mtmp->mtame || mtmp == u.ustuck) goto found_you;


    if (mx == u.ux && my == u.uy) goto found_you;

    notseen = (!mtmp->mcansee || (Invis && !perceives(mtmp->data)));

    if (notseen || Underwater) {

        if ((mtmp->data == &mons[PM_XORN]) && u.ugold && !Underwater)
                disp = 0;
        else
                disp = 1;
    } else if (Displaced) {
        disp = couldsee(mx, my) ? 2 : 1;
    } else disp = 0;
    if (!disp) goto found_you;


    gotu = notseen ? !rn2(3) : Displaced ? !rn2(4) : false;

    if (!gotu) {
        register int try_cnt = 0;
        do {
            if (++try_cnt > 200) goto found_you;
            mx = u.ux - disp + rn2(2*disp+1);
            my = u.uy - disp + rn2(2*disp+1);
        } while (!isok(mx,my)
                 || (disp != 2 && mx == mtmp->mx && my == mtmp->my)
                 || ((mx != u.ux || my != u.uy) &&
                     !passes_walls(mtmp->data) &&
                     (!ACCESSIBLE(levl[mx][my].typ) ||
                      (closed_door(mx, my) && !can_ooze(mtmp))))
                 || !couldsee(mx, my));
    } else {
found_you:
        mx = u.ux;
        my = u.uy;
    }

    mtmp->mux = mx;
    mtmp->muy = my;
}
