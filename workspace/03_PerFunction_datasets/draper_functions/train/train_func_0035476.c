phenotype(unsigned int n) const
{
  if(n >= ptype->nPhenotypes()){
    GAErr(GA_LOC, className(), "phenotype", gaErrBadPhenotypeID);
    return(0.0);
  }
  float val=0.0;
  decode(val,
	 &(data[ptype->offset(n)]), ptype->length(n),
	 ptype->min(n), ptype->max(n));
  return val;
}
