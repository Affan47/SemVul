bindp(node *args, node *list, env *fnenv)
{
   node *head = car(list);
   node *rest = cdr(list);

   if (args->opr.op[0]->ival != wildcard)
   {
      binding *headb = bindnew(args->opr.op[0]->ival, head);
      envext(fnenv, headb);
   }

   if (args->opr.op[1]->type == t_symbol)
   {
      if (args->opr.op[1]->ival != wildcard)
      {
         binding *restb = bindnew(args->opr.op[1]->ival, rest);
         envext(fnenv, restb);
      }
   }
   else
      bindp(args->opr.op[1], rest, fnenv);
}
