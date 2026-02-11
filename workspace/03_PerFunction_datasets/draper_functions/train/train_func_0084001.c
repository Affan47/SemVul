LI27()

{	 VMB27 VMS27 VMV27
	goto TTL;
TTL:;
	{object V167;
	object V168;
	object V169;
	V167= Cnil;
	V168= Cnil;
	V169= Cnil;
	{object V170;
	if(((*(LnkLI10))((((object)VV[35])->s.s_dbind),((object)VV[104])))==Cnil){
	goto T442;}
	V170= list(2,((object)VV[105]),(*(LnkLI256))());
	goto T440;
	goto T442;
T442:;
	V170= (*(LnkLI256))();
	goto T440;
T440:;
	V167= (*(LnkLI272))();
	{object V171;
	V172= (*(LnkLI255))();
	V171= (*(LnkLI13))(V172);
	if(((*(LnkLI10))((V171),((object)VV[106])))==Cnil){
	goto T446;}
	(void)((*(LnkLI256))());
	V168= Ct;
	V169= (*(LnkLI272))();}
	goto T446;
T446:;
	V173= nreverse((V167));
	V174= make_cons((V170),V173);
	if((V168)==Cnil){
	V175= Cnil;
	goto T454;}
	V176= nreverse((V169));
	V177= make_cons(Ct,V176);
	V175= make_cons(V177,Cnil);
	goto T454;
T454:;
	V178= listA(3,((object)VV[14]),V174,V175);
	{object V179 = make_cons(V178,Cnil);
	VMR27(V179)}}}
	return Cnil;
}
