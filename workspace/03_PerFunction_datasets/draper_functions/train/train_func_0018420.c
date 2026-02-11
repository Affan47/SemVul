L20()
{register object *base=vs_base;
	register object *sup=base+VM20; VC20
	vs_check;
	{object V90;
	object V91;
	object V92;
	object V93;
	V90=(base[0]);
	V91=(base[1]);
	V92=(base[2]);
	V93=(base[3]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object V94;
	V94= Cnil;
	V94= immnum_minus((V90),(V91));
	if(!(immnum_lt((V94),small_fixnum(0)))){
	goto T129;}
	base[4]= immnum_plus((V94),(V92));
	vs_top=(vs_base=base+4)+1;
	return;
	goto T129;
T129:;
	base[4]= (V94);
	vs_top=(vs_base=base+4)+1;
	return;
	base[4]= Cnil;
	vs_top=(vs_base=base+4)+1;
	return;
	base[4]= Cnil;
	vs_top=(vs_base=base+4)+1;
	return;}
	}
}
