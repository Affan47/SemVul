LI34__BREAK_FORWARD_SEARCH_STACK__top(V270)

object V270;
{	 VMB34 VMS34 VMV34
	goto TTL;
TTL:;
	{register object V271;
	V271= Cnil;
	V271= coerce_to_string((V270));
	{register object V272;
	register object V273;
	V272= one_plus((((object)VV[73])->s.s_dbind));
	base[0]= (V272);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk217)();
	vs_top=sup;
	V273= vs_base[0];
	goto T1106;
T1106:;
	if(!(immnum_gt((V272),(((object)VV[72])->s.s_dbind)))){
	goto T1107;}
	base[0]= (((object)VV[81])->s.s_dbind);
	base[1]= ((object)VV[151]);
	base[2]= (V271);
	vs_top=(vs_base=base+0)+3;
	Lformat();
	vs_top=sup;
	{object V274 = vs_base[0];
	VMR34(V274)}
	goto T1107;
T1107:;
	if(((*(LnkLI216))((V272)))==Cnil){
	goto T1114;}
	V275= symbol_name((V273));
	V276= (((object)VV[246])->s.s_gfdef);
	if(((VFUN_NARGS=4,(*(LnkLI245))((V271),V275,((object)VV[137]),V276)))==Cnil){
	goto T1114;}
	base[0]= (V272);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk247)();
	vs_top=sup;
	{object V277 = Cnil;
	VMR34(V277)}
	goto T1114;
T1114:;
	V272= one_plus((V272));
	base[0]= (V272);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk217)();
	vs_top=sup;
	V273= vs_base[0];
	goto T1106;}}
	base[0]=base[0];
	return Cnil;
}
