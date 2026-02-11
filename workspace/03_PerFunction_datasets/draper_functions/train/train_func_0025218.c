LI19(V76)

register object V76;
{	 VMB19 VMS19 VMV19
	goto TTL;
TTL:;
	if(type_of((V76))==t_cons){
	goto T297;}
	{object V77 = Cnil;
	VMR19(V77)}
	goto T297;
T297:;{object V78;
	if((CMPcar((V76)))==(((object)VV[17]))){
	goto T301;}
	V78= Cnil;
	goto T300;
	goto T301;
T301:;
	V78= ((STREF(object,CMPcadr((V76)),8))==(((object)VV[27]))?Ct:Cnil);
	goto T300;
T300:;
	if(V78==Cnil)goto T299;
	{object V79 = V78;
	VMR19(V79)}
	goto T299;
T299:;}
	if(!((CMPcar((V76)))==(((object)VV[28])))){
	goto T303;}
	{object V80 = Ct;
	VMR19(V80)}
	goto T303;
T303:;
	{object V81 = ((CMPcar((V76)))==(((object)VV[29]))?Ct:Cnil);
	VMR19(V81)}
	return Cnil;
}
