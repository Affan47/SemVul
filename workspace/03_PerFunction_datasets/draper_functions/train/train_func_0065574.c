reset(int sockcount)
{
	delete[] drawer;

	drawer = new Socket[sockcount];
	socknum = sockcount;
}
