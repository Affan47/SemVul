fight(boolean to_the_death)
{
    short ch, c;
    short row, col;
    short possible_damage;
    object *monster;

    ch = get_direction();
    if (ch == CANCEL) {
	return;
    }
    row = rogue.row;
    col = rogue.col;
    get_dir_rc(ch, &row, &col, 0);

    c = mvinch_rogue(row, col);
    if (((c < 'A') || (c > 'Z')) ||
	(!can_move(rogue.row, rogue.col, row, col))) {
	message(mesg[25], 0);
	return;
    }
    if (!(fight_monster = object_at(&level_monsters, row, col))) {
	return;
    }
    if (!(fight_monster->m_flags & STATIONARY)) {
	possible_damage = ((get_damage(fight_monster->m_damage, 0) * 2) / 3);
    } else {
	possible_damage = fight_monster->stationary_damage - 1;
    }
    while (fight_monster) {
	(void) one_move_rogue(ch, 0);
	if (((!to_the_death) && (rogue.hp_current <= possible_damage)) ||
	    interrupted || (!(dungeon[row][col] & MONSTER))) {
	    fight_monster = 0;
	} else {
	    monster = object_at(&level_monsters, row, col);
	    if (monster != fight_monster) {
		fight_monster = 0;
	    }
	}
    }
}
