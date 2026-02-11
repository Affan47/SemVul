L122__PICMENU_CREATE_SPEC__dwtrans()
{register object *base=vs_base;
	register object *sup=base+VM122; VC122
	vs_check;
	{object V683;
	object V684;
	object V685;
	object V686;
	object V687;
	object V688;
	V683=(base[0]);
	V684=(base[1]);
	V685=(base[2]);
	V686=(base[3]);
	vs_base=vs_base+4;
	if(vs_base>=vs_top){vs_top=sup;goto T2688;}
	V687=(base[4]);
	vs_base++;
	if(vs_base>=vs_top){vs_top=sup;goto T2689;}
	V688=(base[5]);
	vs_top=sup;
	goto T2690;
	goto T2688;
T2688:;
	V687= Cnil;
	goto T2689;
T2689:;
	V688= Cnil;
	goto T2690;
T2690:;
	if((V688)!=Cnil){
	V689= (V688);
	goto T2693;}
	V689= ((object)VV[73]);
	goto T2693;
T2693:;
	base[6]= list(7,((object)VV[79]),(V684),(V685),(V683),(V687),(V686),V689);
	vs_top=(vs_base=base+6)+1;
	return;
	}
}
