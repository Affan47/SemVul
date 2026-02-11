mv_mons(void)
{
    object *monster, *next_monster;
    boolean flew;

    if (haste_self % 2) {
	return;
    }

    monster = level_monsters.next_monster;

    while (monster) {
	next_monster = monster->next_monster;
	if (monster->m_flags & HASTED) {
	    mon_disappeared = 0;
	    mv_monster(monster, rogue.row, rogue.col);
	    if (mon_disappeared) {
		goto NM;
	    }
	} else if (monster->m_flags & SLOWED) {
	    monster->slowed_toggle = !monster->slowed_toggle;
	    if (monster->slowed_toggle) {
		goto NM;
	    }
	}
	if ((monster->m_flags & CONFUSED) && move_confused(monster)) {
	    goto NM;
	}
	flew = 0;
	if ((monster->m_flags & FLIES) && !(monster->m_flags & NAPPING)
	    && !mon_can_go(monster, rogue.row, rogue.col)) {
	    flew = 1;
	    mv_monster(monster, rogue.row, rogue.col);
	}
	if (!(flew && mon_can_go(monster, rogue.row, rogue.col))) {
	    mv_monster(monster, rogue.row, rogue.col);
	}
    NM:
	monster = next_monster;
    }
}
