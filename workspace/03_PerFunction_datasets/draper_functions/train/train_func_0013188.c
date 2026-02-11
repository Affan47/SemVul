shot_over(std::vector<Ball> &balls) {
	moving mv = for_each(balls.begin(), balls.end(), moving());
	if (!mv.is_moving)
		return true;
	else
		return false;
}
