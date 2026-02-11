L1__MAKE_FN__collectfn()
{register object *base=vs_base;
	register object *sup=base+VM1; VC1
	vs_check;
	{object V1;
	object V2;
	object V3;
	object V4;
	object V5;
	object V6;
	object V7;
	object V8;
	object V9;
	parse_key(vs_base,FALSE,FALSE,9,VV[7],VV[15],VV[85],VV[86],VV[87],VV[67],VV[68],VV[88],VV[89]);vs_top=sup;
	V1=(base[0]);
	V2=(base[1]);
	V3=(base[2]);
	V4=(base[3]);
	V5=(base[4]);
	V6=(base[5]);
	V7=(base[6]);
	V8=(base[7]);
	V9=(base[8]);
	base[18]= ((object)VV[0]);
	base[19]= (V1);
	base[20]= (V2);
	base[21]= (V3);
	base[22]= (V4);
	base[23]= (V5);
	base[24]= (V6);
	base[25]= (V7);
	base[26]= (V8);
	base[27]= (V9);
	vs_top=(vs_base=base+18)+10;
	siLmake_structure();
	return;
	}
}
