same_state(const State& s1, const State& s2) {
	if (s1.num_F != s2.num_F)
		return false;
	for (int i=0; i<s1.num_F;i++)
		if (!is_in_state(s1.F[i], &s2))
			return false;
	return true;
}
