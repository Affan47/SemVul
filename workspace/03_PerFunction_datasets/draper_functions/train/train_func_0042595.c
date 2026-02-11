walkfieldarray(Symbol* basetype, Datasrc* src, Dimset* dimset, int index)
{
    int i;
    int rank = dimset->ndims;
    int lastdim = (index == (rank-1));
    Symbol* dim = dimset->dimsyms[index];
    size_t datasize = dim->dim.declsize;
    size_t count = 0;

    ASSERT(datasize != 0);
    count = datasize;
    for(i=0;i<datasize;i++) {
        if(lastdim)
	    walktype(basetype,src,NULL);
	else
	    walkfieldarray(basetype,src,dimset,index+1);
    }
}
