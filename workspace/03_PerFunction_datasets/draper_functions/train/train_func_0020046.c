pop_last_formula()
{
	if (formulas.size() == 0)
		return -1;
	int t = formulas.back();
	if (formulas.size() == ders.size()) {
		delete ders.back();
		ders.pop_back();
	}
	formulas.pop_back();
	return t;
}
