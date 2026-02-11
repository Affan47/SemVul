boomhit(dx, dy)
int dx, dy;
{
	register int i, ct;
	int boom = S_boomleft;
	struct monst *mtmp;

	bhitpos.x = u.ux;
	bhitpos.y = u.uy;

	for (i = 0; i < 8; i++) if (xdir[i] == dx && ydir[i] == dy) break;
	tmp_at(DISP_FLASH, cmap_to_glyph(boom));
	for (ct = 0; ct < 10; ct++) {
		if(i == 8) i = 0;
		boom = (boom == S_boomleft) ? S_boomright : S_boomleft;
		tmp_at(DISP_CHANGE, cmap_to_glyph(boom));
		dx = xdir[i];
		dy = ydir[i];
		bhitpos.x += dx;
		bhitpos.y += dy;
		if(MON_AT(bhitpos.x, bhitpos.y)) {
			mtmp = m_at(bhitpos.x,bhitpos.y);
			m_respond(mtmp);
			tmp_at(DISP_END, 0);
			return(mtmp);
		}
		if(!ZAP_POS(levl[bhitpos.x][bhitpos.y].typ) ||
		   closed_door(bhitpos.x, bhitpos.y)) {
			bhitpos.x -= dx;
			bhitpos.y -= dy;
			break;
		}
		if(bhitpos.x == u.ux && bhitpos.y == u.uy) {
			if(Fumbling || rn2(20) >= ACURR(A_DEX)) {

				(void) thitu(10, rnd(10), (struct obj *)0,
					"boomerang");
				break;
			} else {
				tmp_at(DISP_END, 0);
				You("skillfully catch the boomerang.");
				return(&youmonst);
			}
		}
		tmp_at(bhitpos.x, bhitpos.y);
		delay_output();
		if(ct % 5 != 0) i++;
#ifdef SINKS
		if(IS_SINK(levl[bhitpos.x][bhitpos.y].typ))
			break;
#endif
	}
	tmp_at(DISP_END, 0);
	return (struct monst *)0;
}
