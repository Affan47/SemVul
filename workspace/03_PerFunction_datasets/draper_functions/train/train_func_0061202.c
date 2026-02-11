eval4(void)
{
	VALUE *l, *r;
	int op;
	arith_t val;

	l = eval5();
	while (1) {
		op = nextarg("*");
		if (!op) { op = nextarg("/");
		 if (!op) { op = nextarg("%");
		  if (!op) return l;
		}}
		G.args++;
		r = eval5();
		val = arithmetic_common(l, r, op);
		freev(l);
		freev(r);
		l = int_value(val);
	}
}
