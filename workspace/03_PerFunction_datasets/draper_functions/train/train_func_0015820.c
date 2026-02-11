G_Set_T(Gen_node g){
  Gen_node ptr;
  double t0;
   if ( Gen_length(g)!=2||
        Can_Be_List(Gen_elt(g,1))!=TRUE ||
        Can_Be_Number(Gen_elt(g,2),Dbl_T)==FALSE)
        return Rerror("Usage: SetT({<Dbl>},Dbl)",g);

   ptr=Gen_lval(Gen_elt(g,1));
   t0=Gen_To_Dbl(Gen_elt(g,2));
   free_Gen_list(Gen_next(g));
   while(ptr!=0){
     if (Can_Be_Vector(ptr,Dbl_T)<1){
       return Rerror("Usage: SetT({<Dbl>},Dbl)",g);
     }
     free_Gen_node(*GMref(Gen_Mtx(ptr),1,GMcols(Gen_Mtx(ptr))));
     *GMref(Gen_Mtx(ptr),1,GMcols(Gen_Mtx(ptr)))=DBLND(t0);
     ptr=Gen_next(ptr);
   }
   return g;
}
