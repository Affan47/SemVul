gather_argument(ns, nc)
	int
		ns,
		nc;
{
	for (;;) {
		ZXchar	c;
		bool	neg = NO;

		if (arg_count < 0) {
			neg = YES;
			negate_arg();
		}
		if (ns != arg_state) {

			arg_state = ns;
			arg_count = nc;
		} else {

			int	t = arg_count;

			switch (ns) {
			case AS_NUMERIC:
				t = t*10 + nc;
				break;
			case AS_NEGSIGN:
				neg = !neg;
				break;
			case AS_TIMES:
				t *= nc;
				break;
			}
			if (t < arg_count)
				complain("arg count overflow");
			arg_count = t;
		}
		if (neg)
			negate_arg();


		c = waitchar();
		if (jisdigit(c)) {
			ns = AS_NUMERIC;
			nc = c - '0';
		} else if (arg_state==AS_TIMES && c=='-') {
			ns = AS_NEGSIGN;
			nc = -1;
		} else {
			Ungetc(c);
			break;
		}
	}
	this_cmd = ARG_CMD;
}
