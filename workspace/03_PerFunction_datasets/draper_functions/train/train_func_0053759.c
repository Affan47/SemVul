isunlimited0(Dimset* dimset)
{
   return (dimset->ndims > 0 && dimset->dimsyms[0]->dim.declsize == NC_UNLIMITED);
}
