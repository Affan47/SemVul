gen
	(
	vector<char>& out,
	Uc_function *fun
	)
	{
	if (nest++ > 0)

		Call_intrinsic(out, fun, Uc_function::get_push_answers());
	if (answers)
		Call_intrinsic(out, fun,
				Uc_function::get_add_answer(), answers);
	vector<char> stmt_code;
	fun->start_breakable(this);
	if (cases)
		{
		fun->adjust_reloffset(out.size() + 3);
		cases->gen(stmt_code, fun);
		fun->adjust_reloffset(-out.size() - 3);
		}
	int stmtlen = stmt_code.size();


	long dist = stmtlen + 3 + 3;
	stmt_code.push_back((char) UC_JMP);
	Write2(stmt_code, -dist);
	stmtlen = stmt_code.size();
	fun->end_breakable(this, stmt_code);
	out.push_back((char) UC_CONVERSE);
	Write2(out, stmtlen);

	out.insert(out.end(), stmt_code.begin(), stmt_code.end());
	out.push_back((char) UC_CONVERSELOC);
	if (--nest > 0)

		Call_intrinsic(out, fun, Uc_function::get_pop_answers());
	}
