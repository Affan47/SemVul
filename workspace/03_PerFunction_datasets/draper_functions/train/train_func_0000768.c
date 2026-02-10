CalcConUI(Const_table *lCon, Const_table *rCon, qr_operator ope,
	 int invertl, int invertr)
{
    unsigned int l=0, r=0;

    l = const_table_unsigned_value(lCon);
    r = const_table_unsigned_value(rCon);

    switch(ope){
    case OPE_ADD:
	if(!(invertl) && !(invertr)) return l + r;
	if(!(invertl) && invertr) return l - r;
	if(invertl && !(invertr)) return r - l;
	if(invertl && invertr) return -r - l;
    case OPE_SUB:
	if(!(invertl) && !(invertr)) return l - r;
	if(!(invertl) && invertr) return l + r;
	if(invertl && !(invertr)) return -l - r;
	if(invertl && invertr) return r - l;
    case OPE_MUL:
	if(!(invertl) && !(invertr)) return l * r;
	if(!(invertl) && invertr) return l / r;
	if(invertl && !(invertr)) return r / l;
	if(invertl && invertr) return 1/(l*r);
    case OPE_DIV:
	return l / r;
    default:
	perror("Don't match operator!\n");
	exit(-1);
    }
}
