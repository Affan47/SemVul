LI5(V55,V56)

object V55;object V56;
{	 VMB5 VMS5 VMV5
	goto TTL;
TTL:;
	if(((V56))!=Cnil){
	goto T149;}
	{object V57 = (V55);
	VMR5(V57)}
	goto T149;
T149:;
	V55= elt((V55),fix(car((V56))));
	V56= cdr((V56));
	goto TTL;
	return Cnil;
}
