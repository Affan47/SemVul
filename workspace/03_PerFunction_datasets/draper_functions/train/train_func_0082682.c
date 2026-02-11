nciter_vartype(Symbol* sym, Symbol** tsymp)
{
    if(tsymp)
	*tsymp = sym->typ.basetype;
    return NC_NOERR;
}
