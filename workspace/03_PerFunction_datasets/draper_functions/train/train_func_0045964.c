cmd_bk()
{
	BookEntry entry;
	if (book && book->lookup(game->get_board(), &entry)) {
		entry.print(game->get_board());
	} else {
		printf(" Nothing found in book\n");
	}


	printf("\n");
}
