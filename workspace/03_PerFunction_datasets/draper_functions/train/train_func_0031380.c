__bld_loc_lds_iterator(struct h_t *hp, int32 otype)
{
 if (hp == NULL) return(__nil_iter_err(otype));


 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   return(net_lds_iter(hp));
  case vpiNetBit: case vpiRegBit: case vpiVarSelect:
   return(bit_lds_iter(hp));
  default:
   __vpi_err(1874, vpiError,
    "vpiLocalLoad 1-to-many iterator from %s illegal - for net/reg/variable loads",
    __to_vpionam(__wrks1, hp->hrec->htyp));
  }
 return(NULL);
}
