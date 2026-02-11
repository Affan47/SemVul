nciter_dimlens(Symbol* sym, size_t* dimlens)
{
    int i;
    int ndims = sym->typ.dimset.ndims;
    for(i=0;i<ndims;i++) {
	Symbol* dim = sym->typ.dimset.dimsyms[i];
	dimlens[i] = MAX(dim->dim.declsize,dim->dim.unlimitedsize);
    }
    return NC_NOERR;
}
