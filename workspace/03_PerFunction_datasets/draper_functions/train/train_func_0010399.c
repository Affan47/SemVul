print_eval(const Board & board, Color _myside, FILE * fp)
{
	myside = _myside;
	setup(&board);

	fprintf(fp, "material: %d/%d\n",
			board.material[WHITE], board.material[BLACK]);
	fprintf(fp, "material difference: %d\n",
			board.material[WHITE] - board.material[BLACK]);
	fprintf(fp, "material balance: %d\n",
			 material_balance(board.material[WHITE],
				 	  board.material[BLACK]));
	fprintf(fp, "phase: %u\n", phase);

	fprintf(fp, "draw: %s\n", is_draw(board) ? "yes" : "no");
	fprintf(fp, "myside: %s\n",
			(myside == WHITE ? "white"
		 		: (myside == BLACK ? "black" : "none")));

	fprintf(fp, "scoring plugins:\n");
	for (int i=0; plugins[i].name != NULL; i++) {
		ASSERT(plugins[i].func != NULL);
		fprintf(fp, "\t%s: %d/%d\n", plugins[i].name,
				(this->*plugins[i].func)(WHITE),
				(this->*plugins[i].func)(BLACK));
	}

	fprintf(fp, "scoring plugins2:\n");
	for (int i=0; plugins2[i].name != NULL; i++) {
		ASSERT(plugins2[i].func != NULL);
		fprintf(fp, "\t%s: %d/%d\n", plugins2[i].name,
				(this->*plugins2[i].func)(WHITE),
				(this->*plugins2[i].func)(BLACK));
	}
}
