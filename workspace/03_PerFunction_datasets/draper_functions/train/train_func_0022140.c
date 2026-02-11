lcl_tend(n)
struct node *n;
   {
   struct sym_entry *sym;

   if (n == NULL)
      return;


   switch (n->nd_id) {
      case PrefxNd:
      case PstfxNd:
      case PreSpcNd:
        lcl_tend(n->u[0].child);
        break;
      case BinryNd:
      case LstNd:
      case ConCatNd:
      case CommaNd:
      case StrDclNd:
        lcl_tend(n->u[0].child);
        lcl_tend(n->u[1].child);
        break;
      case CompNd:


         for (sym = n->u[1].sym; sym != NULL; sym = sym->u.tnd_var.next) {
            sym->t_indx = alloc_tnd(sym->id_type, sym->u.tnd_var.init,
               sym->nest_lvl - 1);
            }
         lcl_tend(n->u[2].child);
         sym = n->u[1].sym;
         if (sym != NULL)
            unuse(tend_lst, sym->nest_lvl - 1);
         break;
      case TrnryNd:
         lcl_tend(n->u[0].child);
         lcl_tend(n->u[1].child);
         lcl_tend(n->u[2].child);
         break;
      case QuadNd:
         lcl_tend(n->u[0].child);
         lcl_tend(n->u[1].child);
         lcl_tend(n->u[2].child);
         lcl_tend(n->u[3].child);
         break;
      }
   }
