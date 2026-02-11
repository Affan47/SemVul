print(FILE * fp) const
{
	fprintf(fp, "Positions in game history: %d\n", entries.size());
	for (std::list<GameEntry>::const_iterator it = entries.begin();
			it != entries.end(); it++) {
		fprintf(fp, "---------------------------------------------\n");
		it->get_board().print_small(fp);
		fprintf(fp, "\n");

		fprintf(fp, "White clock:\n");
		it->get_clock(WHITE).print(fp);
		fprintf(fp, "Black clock:\n");
		it->get_clock(BLACK).print(fp);
		fprintf(fp, "\n");

		fprintf(fp, "Move played: %s\n",
				it->get_move().san(it->get_board()).c_str());
		fprintf(fp, "Move attributes:");
		if (it->get_attr().computer) fprintf(fp, " computer");
		if (it->get_attr().bookmove) fprintf(fp, " bookmove");
		fprintf(fp, "\n\n");
	}
}
