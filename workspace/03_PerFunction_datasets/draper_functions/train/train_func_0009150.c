L44()
{register object *base=vs_base;
	register object *sup=base+VM44; VC44
	vs_check;
	{object V157;
	object V158;
	object V159;
	object V160;
	V157=(base[0]);
	V158=(base[1]);
	V159=(base[2]);
	V160=(base[3]);
	vs_top=sup;
	goto TTL;
TTL:;
	V161= immnum_times((V157),(V158));
	base[4]= immnum_rem(V161,(V159));
	vs_top=(vs_base=base+4)+1;
	return;
	}
}
