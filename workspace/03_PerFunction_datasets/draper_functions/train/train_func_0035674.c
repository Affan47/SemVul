ptr_arith(void)
{
	struct Foo_normal foo[10];
	int i;

	struct Foo_normal *foo_ptr = &foo[0];
	for (i = 0; i < 10; i++)
		foo[i].a = i;

	for (i = 0; i < 10; i++)
		printf("foo[%d].a = %d\n", i, (foo_ptr++)->a);
}
