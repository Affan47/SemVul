LI16(V212,V213)

register object V212;object V213;
{	 VMB16 VMS16 VMV16
	goto TTL;
TTL:;
	{register long V214;
	register long V215;
	register object V216;
	register object V217;
	V214= (long)length((V212));
	V215= (long)8;
	V216= CMPmake_fixnum((long)((*(LnkLI352))((V213))));
	V217= Ct;
	goto T734;
T734:;
	if(eql(small_fixnum(0),(V216))){
	goto T736;}
	V214= (long)(V214)+((long)((fix((V216))) << (V215)));
	goto T736;
T736:;
	if(((V217))==Cnil){
	goto T740;}
	V215= (long)10;
	V217= Cnil;
	goto T740;
T740:;
	if(((V212))!=Cnil){
	goto T746;}
	{long V218 = V214;
	VMR16((object)V218)}
	goto T746;
T746:;
	V215= (long)(V215)+((long)2);
	{register object V220;
	V220= CMPcar((V212));
	V212= CMPcdr((V212));
	V219= (V220);}
	V216= CMPmake_fixnum((long)((*(LnkLI352))(V219)));
	goto T734;}
}
