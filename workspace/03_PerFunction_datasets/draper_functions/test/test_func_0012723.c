set_ret(typ)
#ifdef OptimizeType
struct typinfo *typ;
#else
unsigned int *typ;
#endif
   {
   int i;


   if (typ != NULL)
      deref_lcl(typ, cur_proc->ret_typ);


   for (i = 0; i < n_gbl; ++i)
      MrgTyp(n_icntyp, succ_store->types[i], cur_proc->out_store->types[i]);
   }
