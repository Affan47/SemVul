phenotype(unsigned int n, float val)
{
  if(n >= ptype->nPhenotypes()){
    GAErr(GA_LOC, className(), "phenotype", gaErrBadPhenotypeID);
    return val;
  }
  if(val < ptype->min(n) || val > ptype->max(n)){
    GAErr(GA_LOC, className(), "phenotype", gaErrBadPhenotypeValue);
    val = ((val < ptype->min(n)) ? ptype->min(n) : ptype->max(n));
  }
  encode(val,
	 &(data[ptype->offset(n)]), ptype->length(n),
	 ptype->min(n), ptype->max(n));
  return val;
}
