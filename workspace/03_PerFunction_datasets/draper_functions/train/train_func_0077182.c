reset()
{
	int new_board[32];

	for(int i=0; i<12; i++)
		new_board[i]=MAN2;
	for(int i=12; i<20; i++)
		new_board[i]=FREE;
	for(int i=20; i<32; i++)
		new_board[i]=MAN1;


	for(int i=0; i<32; i++)
		m_fields[i]->showFrame(false);

	if(m_game)
		m_game->setup(new_board);

	do_draw();
}
