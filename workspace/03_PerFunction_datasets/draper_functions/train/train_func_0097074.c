get_obj_index(struct h_t *hp)
{
 register word32 av;
 register struct hrec_t *hrp;
 vpiHandle ihref;
 struct h_t *rhp;

 hrp = hp->hrec;
 switch (hrp->htyp) {
  case vpiMemoryWord: case vpiNetBit: case vpiRegBit: case vpiVarSelect:

   if (hrp->bith_ndx)
    {

     av = (word32) __unnormalize_ndx(hrp->hu.hnp, hrp->hi);


bld_const_obj:
     ihref = __mk_handle(vpiConstant, NULL, hp->hin_itp, hrp->hin_tskp);
     rhp = (struct h_t *) ihref;
     rhp->hrec->hu.hxp = __bld_rng_numxpr(av, 0L, WBITS);
     rhp->hrec->free_xpr = TRUE;
     break;
    }


   if (hrp->hu.hxp->optyp != LSB) __vpi_terr(__FILE__, __LINE__);

   ihref = __mk_exprclass_handle(hrp->hu.hxp->ru.x, hp->hin_itp,
    hrp->hin_tskp);
   break;
  case vpiPortBit:

   av = (word32) hrp->hi;
   goto bld_const_obj;
  default: no_1to1h_err(vpiIndex, hp); return(NULL);
 }
 return(ihref);
}
