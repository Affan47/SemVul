cdr(node *node)
{
   struct node *ret;

   switch (node->opr.nops)
   {
      case 0:
      case 1:
         ret = mkcons(LIST, 0);
         break;
      case 2:
         ret = node->opr.op[1];
         incref(ret);
         break;
   }

   decref(node);
   return ret;
}
