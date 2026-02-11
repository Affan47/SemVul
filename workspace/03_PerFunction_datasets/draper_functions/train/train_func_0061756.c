add_unit_vec(angle_c dir, int *fived)
{
	static const int dir2i[] = {0, 3, 1, 4, 2};

	while (dir < 0)
		dir += 10;
	fived[dir2i[dir % 5]] += (dir % 2 ? -1 : 1);
}
