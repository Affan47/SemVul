mod(void)
{
	Datum d1, d2;
	d2 = pop();
	if (d2.val == 0.0)
		execerror("division by zero", (char *)0);
	d1 = pop();

	d1.val = fmod(d1.val, d2.val);
	push(d1);
}
