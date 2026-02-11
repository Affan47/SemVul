lbl(t)
struct token *t;
   {
   struct sym_entry *sym;
   struct node *n;

   sym = sym_add(Identifier, t->image, Label, 2);
   if (sym == NULL)
      errt2(t, "conflicting definitions for ", t->image);
   n = sym_node(t);
   if (n->u[0].sym != sym)
      errt2(t, "conflicting definitions for ", t->image);
   return n;
   }
