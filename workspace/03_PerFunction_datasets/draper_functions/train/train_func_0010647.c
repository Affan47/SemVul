loadV2(std::istream &input, Game &g)
{
    BitBoard64 mask;
    input >> mask;
    g.setMask(mask);

	uint32_t nr;
	input >> nr;

	g.boardList.clear();

	while(nr)
	{
        Board tmp;
        int turn;

        input >> tmp;
        input >> turn;

		g.boardList.push_back(make_pair(tmp, turn));

		nr--;
	}

	g.pos = g.boardList.begin();
	while(g.next() == 0)
		;
}
