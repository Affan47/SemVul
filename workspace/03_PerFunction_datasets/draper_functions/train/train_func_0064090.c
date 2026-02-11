parse_level3(Object& left)
{
	Object op = parse_level4(left);
	if (left.gettype() != Object::type_scalar)
		return op;
	while ((op.gettype() == Object::type_token) &&
		(op.token().type == token_operator) &&
		((op.token().value[0] == '+') ||
		(op.token().value[0] == '-')))
	{
		Object right = lex.getstricttoken();

		Object nextop = parse_level4(right);
		int64_t lwork = str2num(left.scalar().c_str()),
			rwork = str2num(right.scalar().c_str());
		switch (op.token().value[0])
		{
		case '+':
			lwork+= rwork;
			break;
		case '-':
			lwork-= rwork;
			break;
		}
		num2str(lwork, left.scalar());

		op = nextop;
	}
	return op;
}
