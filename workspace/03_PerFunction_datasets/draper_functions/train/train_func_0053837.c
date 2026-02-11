paramprop_vpiget(struct h_t *hp, int32 prop)
{
 struct net_t *np;

 np = hp->hrec->hu.hnp;
 switch (prop) {


  case vpiConstType: return(get_param_constyp(np));
  case vpiLineNo: return(np->nsym->sylin_cnt);
  case vpiSize: return(np->nwid);
  case vpiLocalParam:
   if (np->nu.ct->p_locparam) return(TRUE);
   return(FALSE);
  case vpiSigned:

   if (hp->hrec->htyp == vpiParameter)
    {
     if (np->n_signed) return(TRUE);
     return(FALSE);
    }

  default: notpropof_err(hp->hrec->htyp, prop); break;
 }
 return(vpiUndefined);
}
