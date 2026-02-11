rd_contassign(void)
{
 struct expr_t *lhsndp, *rhsndp;
 struct paramlst_t *pmphdr;
 struct conta_t *cap;
 int32 first_time, sfnind, slcnt;


 pmphdr = NULL;
 __v0stren = __v1stren = NO_STREN;

 __get_vtok();
 if (__toktyp == LPAR)
  {
   __get_vtok();
   if (!rd_verstrens())
    {
     if (!__vskipto2_any(RPAR, SEMI)) return(FALSE);
     if (__toktyp == RPAR) { __get_vtok(); goto rd_parms; }
     return(TRUE);
    }
  }

rd_parms:
 if (__toktyp == SHARP)
  {
   if (!rd_oparamdels(&pmphdr))
    {
bad_end:
     return(__vskipto_any(SEMI));
    }
  }
 for (first_time = TRUE;;)
  {
   sfnind = __cur_fnam_ind;
   slcnt = __lin_cnt;

   if (!__col_lval()) goto bad_end;
   __bld_xtree(0);

   lhsndp = __root_ndp;
   __get_vtok();
   if (!__col_comsemi(-1)) goto bad_end;
   __bld_xtree(0);
   rhsndp = __root_ndp;
   cap = add_conta(lhsndp, rhsndp, sfnind, slcnt);
   if (first_time) cap->ca_du.pdels = pmphdr;
   else cap->ca_du.pdels = __copy_dellst(pmphdr);

   if (__v0stren != NO_STREN)
    {
     cap->ca_hasst = TRUE;
     cap->ca_stval = ((__v0stren << 3) | __v1stren) & 0x3f;
    }
   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA)
    {

     if (!__vskipto2_any(COMMA, SEMI)) return(FALSE);
     if (__toktyp == SEMI) break;
    }
   first_time = FALSE;
   __get_vtok();
  }
 return(TRUE);
}
