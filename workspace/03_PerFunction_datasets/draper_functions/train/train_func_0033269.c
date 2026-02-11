add_literal(int l) {
	assert(abs(l) >= 1 && abs(l) <= Clause::num_bool_vars());

	if (contain(l)) return;


	clause.push_back(l);
	sort(clause.begin(), clause.end());
}
