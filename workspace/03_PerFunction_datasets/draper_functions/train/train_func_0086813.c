LC37(base0)
register object *base0;
{	register object *base=vs_base;
	register object *sup=base+VM14; VC14
	vs_reserve(VM14);
	ihs_check;
	{object V130;
	check_arg(1);
	V130=(base[0]);
	vs_top=sup;
	base[1]=symbol_function(((object)VV[105]));
	base[2]= small_fixnum(1);
	base[3]= (V130);
	vs_top=(vs_base=base+2)+2;
	funcall_with_catcher(((object)VV[105]),base[1]);
	return;
	}
}
