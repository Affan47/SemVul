potion_monster(object *monster, unsigned short kind)
{
    short maxhp;

    maxhp = mon_tab[monster->m_char - 'A'].hp_to_kill;

    switch (kind) {
    case RESTORE_STRENGTH:
    case LEVITATION:
    case HALLUCINATION:
    case DETECT_MONSTER:
    case DETECT_OBJECTS:
    case SEE_INVISIBLE:
	break;
    case EXTRA_HEALING:
	monster->hp_to_kill += (maxhp - monster->hp_to_kill) * 2 / 3;
	break;
    case INCREASE_STRENGTH:
    case HEALING:
    case RAISE_LEVEL:
	monster->hp_to_kill += (maxhp - monster->hp_to_kill) / 5;
	break;
    case POISON:
	mon_damage(monster, (monster->hp_to_kill / 4 + 1));
	break;
    case BLINDNESS:
	monster->m_flags |= (ASLEEP | WAKENS);
	break;
    case CONFUSION:
	monster->m_flags |= CONFUSED;
	monster->moves_confused += get_rand(12, 22);
	break;
    case HASTE_SELF:
	if (monster->m_flags & SLOWED)
	    monster->m_flags &= (~SLOWED);
	else
	    monster->m_flags |= HASTED;
	break;
    }
}
