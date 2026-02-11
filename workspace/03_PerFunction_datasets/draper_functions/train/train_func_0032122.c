filltypecodes(void)
{
    Symbol* sym;
    for(sym=symlist;sym != NULL;sym = sym->next) {
	if(sym->typ.basetype != NULL && sym->typ.typecode == NC_NAT)
	    sym->typ.typecode = sym->typ.basetype->typ.typecode;
    }
}
