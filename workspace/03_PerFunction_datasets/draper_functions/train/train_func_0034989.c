L24()
{register object *base=vs_base;
	register object *sup=base+VM24; VC24
	vs_check;
	{object V130;
	object V131;
	V130=(base[0]);
	V131=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object V132;
	V132= (*(LnkLI105))((V130));
	{object V133;
	V133= STREF(object,(V131),32);
	{register long V134;
	V134= (long)0;
	goto T188;
T188:;
	if(!((V134)==((long)((V133))->v.v_fillp))){
	goto T189;}
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	goto T189;
T189:;
	{register object V135;
	V135= ((V133))->v.v_self[V134];
	{register object V136;
	V136= (*(LnkLI105))((V135));
	if((STREF(object,(V130),32))!=Cnil){
	goto T199;}
	goto T198;
	goto T199;
T199:;
	if(eql(STREF(object,(V130),32),(V136))){
	goto T196;}
	goto T198;
T198:;
	if((STREF(object,(V135),32))!=Cnil){
	goto T203;}
	goto T202;
	goto T203;
T203:;
	if(eql(STREF(object,(V135),32),(V132))){
	goto T196;}
	goto T202;
T202:;
	if((V132)==Cnil){
	goto T193;}
	if(!(eql((V132),(V136)))){
	goto T193;}
	goto T196;
T196:;
	base[2]= Ct;
	vs_top=(vs_base=base+2)+1;
	return;}}
	goto T193;
T193:;
	V134= (long)(V134)+1;
	goto T188;}}}
	}
}
