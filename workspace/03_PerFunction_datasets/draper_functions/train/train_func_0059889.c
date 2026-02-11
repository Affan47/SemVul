test_cmp (char *stra, char *strb, int parts, int diff)
{
	iksid *a, *b;

	a = iks_id_new (my_stack, stra);
	b = iks_id_new (my_stack, strb);
	if (diff != iks_id_cmp (a, b, parts)) exit (1);
}
