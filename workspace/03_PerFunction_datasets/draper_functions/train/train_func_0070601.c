G_Aset(Gen_node g){
  psys P;
  aset A=0;


if (Gen_length(g)==1&&Can_Be_Vector(g,Ply_T)>0){

P=Gen_to_psys(g);


    A=psys_to_aset(P);

    psys_free(P);

    return ASTND(A);
  }

 return List_To_Aset(g);
}
