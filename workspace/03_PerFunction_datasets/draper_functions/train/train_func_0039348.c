LI51__MAKE_BREAK_POINT__debug(V564,V565,V566)

object V564;object V565;object V566;
{	 VMB49 VMS49 VMV49
	goto TTL;
TTL:;
	V567= fLrow_major_aref((V565),fixint((V566)));
	V568= fLrow_major_aref((V565),(long)0);
	V569= car(V568);
	V570= fLrow_major_aref((V565),(long)0);
	V571 = make_fixnum((long)((fix(cdr(V570)))+(fix((V566)))));
	{object V572 = list(4,V567,V569,V571,(V564));
	VMR49(V572)}
	return Cnil;
}
