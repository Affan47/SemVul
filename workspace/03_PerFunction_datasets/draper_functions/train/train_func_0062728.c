G_Normalize(Gen_node g){
 Gen_node ptr, res,rptr;
 Dmatrix root;

 if (g==0 ||
     Gen_length(g)!=1 ||
     Can_Be_List(g)!=TRUE)
     return Rerror("Usage: Normalize({<Dbl>})",g);

 rptr=(res=gen_node());
 ptr=Gen_lval(g);
 while(ptr!=0){
   if (Can_Be_Vector(ptr,Dbl_T)!=2*N+3){
      free_Gen_list(Gen_next(res));
      free_Gen_node(res);
       return
        Rerror("Usage: Normalize({<Dbl>})",g);
   }
  root=Gen_to_Dmatrix(ptr);
  xpnt_normalize(root);
  Gen_set_next(rptr,Dmatrix_to_Gen(root));
  rptr=Gen_next(rptr);
  ptr=Gen_next(ptr);
 }
 free_Gen_list(g);
 g=Gen_node_to_List(Gen_next(res));
 free_Gen_node(res);
 return g;
}
