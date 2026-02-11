__qc_tran_wireforce(struct net_t *np, int32 biti, int32 bitj,
 int32 rhsbi, struct itree_t *itp, struct st_t *qcfstp)
{
 register int32 bi;
 word32 aval, bval;
 struct xstk_t *xsp;
 struct expr_t *rhsx;

 rhsx = qcfstp->st.sqca->qcrhsx;


 xsp = __eval_assign_rhsexpr(rhsx, qcfstp->st.sqca->qclhsx);

 if (rhsbi == -1) rhsbi = 0;

 if (!np->n_isavec)
  {


   if (biti != 0 || bitj != 0) __misc_terr(__FILE__, __LINE__);


   aval = rhsbsel_(xsp->ap, rhsbi);
   bval = rhsbsel_(xsp->bp, rhsbi);


   do_qc_wire_intran_force(np, -1, aval, bval, itp);
  }
 else
  {
   for (bi = biti; bi >= bitj; bi--)
    {
     aval = rhsbsel_(xsp->ap, rhsbi + (bi - bitj));
     bval = rhsbsel_(xsp->bp, rhsbi + (bi - bitj));

     do_qc_wire_intran_force(np, bi, aval, bval, itp);
    }
  }
 __pop_xstk();
}
