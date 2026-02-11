attachdims34(CDFnode* xnode, CDFnode* ddsnode)
{
    unsigned int i;
    for(i=0;i<nclistlength(xnode->array.dimensions);i++) {
	CDFnode* xdim = (CDFnode*)nclistget(xnode->array.dimensions,i);
	CDFnode* ddim = (CDFnode*)nclistget(ddsnode->array.dimensions,i);
	setattach(xdim,ddim);
    }
    return NC_NOERR;
}
