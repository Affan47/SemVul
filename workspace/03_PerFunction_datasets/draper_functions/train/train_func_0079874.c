add_forw_pos(pos)
	POSITION pos;
{
	register int i;


	for (i = 1;  i < sc_height;  i++)
		table[i-1] = table[i];
	table[sc_height - 1] = pos;
}
