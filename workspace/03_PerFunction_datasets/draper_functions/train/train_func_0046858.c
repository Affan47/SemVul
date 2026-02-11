bind(node *args, node *params, env *fnenv, env *argenv)
{
   if (params != NULL)
   {
      if (params->opr.nops > 1)
         bind(args->opr.op[1], params->opr.op[1], fnenv, argenv);

      if (params->opr.nops > 0)
      {
         node *n = eval(params->opr.op[0], argenv);

         if (args->opr.op[0]->type == t_symbol)
         {
            binding* b = bindnew(args->opr.op[0]->ival, n);
            envext(fnenv, b);
         }
         else if (args->opr.op[0]->type == t_cons && args->opr.op[0]->opr.oper == CONS)
            bindp(args->opr.op[0], n, fnenv);
      }
   }
}
