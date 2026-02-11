envlookup(env *e, symbol sym)
{
   env *top = e;
   bool depth = false;

   while (e != NULL)
   {
      binding *b = e->bind;

      while (b != NULL)
      {
         if (sym == b->sym)
         {


            return b;
         }

         b = b->prev;
      }

      e = e->parent;
      depth = true;
   }

   return NULL;
}
