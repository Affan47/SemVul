mono_test_marshal_struct_array (simplestruct2 *ss)
{
	if (! (ss[0].a == 0 && ss[0].b == 1 && ss[0].c == 0 &&
		   !strcmp (ss[0].d, "TEST") &&
		   ss[0].e == 99 && ss[0].f == 1.5 && ss[0].g == 42 && ss[0].h == (guint64)123))
		return 1;

	if (! (ss[1].a == 0 && ss[1].b == 0 && ss[1].c == 0 &&
		   !strcmp (ss[1].d, "TEST2") &&
		   ss[1].e == 100 && ss[1].f == 2.5 && ss[1].g == 43 && ss[1].h == (guint64)124))
		return 1;

	return 0;
}
