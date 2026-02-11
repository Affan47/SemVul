preserveContainedCDS(GffObj* t, GffObj* tfrom) {

 if (tfrom->CDstart==0) return;
 if (t->CDstart) {
   if (tfrom->CDstart<t->CDstart && tfrom->CDstart>=t->start)
      t->CDstart=tfrom->CDstart;
   if (tfrom->CDend>t->CDend && tfrom->CDend<=t->end)
      t->CDend=tfrom->CDend;
   }
  else {
   t->addCDS(tfrom->CDstart, tfrom->CDend, tfrom->CDphase);
   }
}
