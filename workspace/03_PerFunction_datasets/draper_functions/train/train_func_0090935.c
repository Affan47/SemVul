applicable(const solver *ego_, const problem *p_,
		      const planner *plnr)
{
     if (!applicable0(ego_, p_, plnr)) return 0;
     {
          const problem_dft *p = (const problem_dft *) p_;
	  if (NO_INDIRECT_OP_P(plnr) && p->ri != p->ro) return 0;
     }
     return 1;
}
