cmp_drvld_bitndx(struct net_t **nnp, struct h_t *hp, char *objnam)
{
 register int32 bi;
 register struct net_t *np;
 register struct hrec_t *hrp;

 *nnp = NULL;
 hrp = hp->hrec;
 if (!hrp->bith_ndx && !__expr_is_vpiconst(hrp->hu.hxp))
  {
   __vpi_err(1880, vpiError,
    "%s 1-to-many iterator from %s illegal - vpiNetBit/vpiRegBit non constant",
    objnam, __to_vpionam(__wrks1, hrp->htyp));
   return(-1);
  }
 if (hrp->bith_ndx) { np = hrp->hu.hnp; bi = hrp->hi; }
 else
  {

   if (hrp->hu.hxp->optyp != LSB) __vpi_terr(__FILE__, __LINE__);


   np = hrp->hu.hxp->lu.sy->el.enp;
   __push_itstk(hp->hin_itp);
   bi = __comp_ndx(np, hrp->hu.hxp->ru.x);
   __pop_itstk();

   if (bi == -1) return(-1);
  }
 *nnp = np;
 return(bi);
}
