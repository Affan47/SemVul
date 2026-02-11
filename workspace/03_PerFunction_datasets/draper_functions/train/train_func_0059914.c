regprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 biti, is_bit;
 struct net_t *np;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 is_bit = FALSE;
 if (hrp->htyp == vpiRegBit || hrp->htyp == vpiVarSelect)
  {
   if (hrp->bith_ndx) np = hrp->hu.hnp;
   else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;
   is_bit = TRUE;
  }
 else np = hrp->hu.hnp;

 switch (prop) {
  case vpiLineNo: return(np->nsym->sylin_cnt);
  case vpiScalar:
   if (np->n_isavec) return(FALSE);
   return(TRUE);
  case vpiSigned:

   if (np->n_signed) return(TRUE);
   return(FALSE);
  case vpiSize:
   if (is_bit) return(1);
   return(np->nwid);
  case vpiVector:
   if (np->n_isavec && !is_bit) return(TRUE);
   return(FALSE);
  case vpiConstantSelect:
   if (hrp->htyp != vpiRegBit && hrp->htyp != vpiVarSelect) goto bad_prop;
   if (hrp->bith_ndx) return(TRUE);
   if (__expr_is_vpiconst(hrp->hu.hxp->ru.x))
    {
     __push_itstk(hp->hin_itp);


     biti = __comp_ndx(np, hrp->hu.hxp->ru.x);
     __pop_itstk();
     if (biti == -1) return(FALSE);
     return(TRUE);
    }
   return(FALSE);
  default:
bad_prop:
   notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}
