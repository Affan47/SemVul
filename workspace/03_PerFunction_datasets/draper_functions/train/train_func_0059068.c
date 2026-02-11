sublis1(alist,tree,tst)
     object alist,tree;
     bool (*tst)();
{object v;
 for (v=alist ; v!=Cnil; v=v->c.c_cdr)
   { if ((*tst)(v->c.c_car->c.c_car ,tree))
       return(v->c.c_car->c.c_cdr);}
 if (type_of(tree)==t_cons)
   {object ntree=make_cons(sublis1(alist,tree->c.c_car,tst),
			   tree->c.c_cdr);
    ntree->c.c_cdr=sublis1(alist,ntree->c.c_cdr,tst);
    return ntree;
  }
  return tree;
}
