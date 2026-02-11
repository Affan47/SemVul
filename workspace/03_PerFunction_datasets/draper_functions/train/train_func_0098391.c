binary_nd(op, arg1, arg2)
nodeptr op;
nodeptr arg1;
nodeptr arg2;
   {
   register nodeptr t;
   struct implement *impl;


   impl = optab[Val0(op)].binary;
   if (impl == NULL)
      nfatal(op, "binary operator not implemented", optab[Val0(op)].tok.t_word);
   else if (impl->in_line == NULL)
      nfatal(op, "binary operator not installed", optab[Val0(op)].tok.t_word);

   t = NewNode(4);
   t->n_type = N_InvOp;
   t->n_file = op->n_file;
   t->n_line = op->n_line;
   t->n_col = op->n_col;
   t->freetmp = NULL;
   t->n_field[0].n_val = 2;
   t->n_field[1].ip = impl;
   t->n_field[2].n_ptr = arg1;
   t->n_field[3].n_ptr = arg2;
   return t;
   }
