aggravate(void)
{
    object *monster;

    message(mesg[65], 0);
    monster = level_monsters.next_monster;

    while (monster) {
	wake_up(monster);
	monster->m_flags &= (~IMITATES);
	if (rogue_can_see(monster->row, monster->col)) {
	    mvaddch_rogue(monster->row, monster->col, monster->m_char);
	}
	monster = monster->next_monster;
    }
}
