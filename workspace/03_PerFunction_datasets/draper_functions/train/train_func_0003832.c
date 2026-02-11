low_ball() {

	int low = 16;
	int cur;
	std::vector<Ball>::iterator bs;
	for (bs=balls.begin(); bs != balls.end(); bs++)
	{
		cur = bs->ball_num;
		if (cur > 0 && cur < 16 && cur < low)
			low = cur;
	}
	return low;
}
