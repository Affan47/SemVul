L25()
{register object *base=vs_base;
	register object *sup=base+VM25; VC25
	vs_check;
	{object V45;
	V45=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;{object V47;
	base[1]= (V45);
	base[2]= (((object)VV[23])->s.s_dbind);
	vs_top=(vs_base=base+1)+2;
	(void) (*Lnk76)();
	vs_top=sup;
	V47= vs_base[0];
	if(V47==Cnil)goto T77;
	V46= V47;
	goto T76;
	goto T77;
T77:;}
	base[1]= (V45);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk77)();
	vs_top=sup;
	V46= vs_base[0];
	goto T76;
T76:;
	base[1]= listA(3,((object)VV[12]),(V45),V46);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
