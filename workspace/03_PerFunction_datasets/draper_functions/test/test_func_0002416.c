mon_name(object *monster)
{
    short ch;

    if (blind || ((monster->m_flags & INVISIBLE) &&
		  !(detect_monster || see_invisible || r_see_invisible))) {
	return mesg[63];
    }
    if (halluc) {
	ch = get_rand('A', 'Z') - 'A';
	return m_names[ch];
    }
    ch = monster->m_char - 'A';
    return m_names[ch];
}
