Lwrite_byte()
{
# line 1836 "print.d"

	int narg;
	register object *DPPbase=vs_base;
#define	integer	DPPbase[0]
#define	binary_output_stream	DPPbase[1]

	narg = vs_top - vs_base;
	check_arg(2);

# line 1837 "print.d"

	if (type_of(integer) != t_fixnum)
		FEerror("~S is not a byte.", 1, integer);
	check_type_stream(&binary_output_stream);
	writec_stream(fix(integer), binary_output_stream);
	{
		vs_base[0] = integer;
		vs_top = vs_base + 1;
		return;
	}
# line 1842 "print.d"

#undef integer
#undef binary_output_stream
}
