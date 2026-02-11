mono_safe_handle_struct_ref (HandleStructs *x)
{
	printf ("Dingus Ref! \n");
	printf ("Values: %d %d %p %p\n", x->a, x->b, x->handle1, x->handle2);
	if (x->a != 1234)
		return 1;
	if (x->b != 8743)
		return 2;

	if (x->handle1 != (void*) 0x7080feed)
		return 3;

	if (x->handle2 != (void*) 0x1234abcd)
		return 4;

	return 0xf00d;
}
