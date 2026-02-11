LI30(V192,V193)

object V192;object V193;
{	 VMB30 VMS30 VMV30
	goto TTL;
TTL:;
	V194= (*(LnkLI19))((V192));
	V195= immnum_negate(V194);
	V196= immnum_shft((V193),V195);
	V197= (*(LnkLI20))((V192));
	V198= one_minus(immnum_shft(small_fixnum(1),V197));
	{object V199 = immnum_and((V196),(V198));
	VMR30(V199)}
	return Cnil;
}
