psys_hom(psys sys, node point_list, int tweak){
  node ptr=point_list;

#ifdef PSYS_HOM_PRINT
  fprintf(stdout ,"S starting continuation:\n");
  fprintf(stdout ,"N");Imatrix_fprint(stdout ,Norm);
  fprintf(stdout ,"P"); psys_fprint(stdout ,sys);
#endif

  if (Cont_Alg==USE_HOMPACK){
     init_hom(sys);
     while(ptr!=0){
       HPK_cont((Dmatrix)Car(Car(ptr)), tweak);
       ptr=Cdr(ptr);
     }
  }
  else {
    while(ptr!=0){

#ifdef PSYS_HOM_PRINT
      fprintf(stdout ,"P"); psys_fprint(stdout ,sys);
      fprintf(stdout ,"X"); Dvector_fprint(stdout ,(Dmatrix)Car(Car(ptr)));
#endif

      psys_cont((Dmatrix)Car(Car(ptr)),sys);
      ptr=Cdr(ptr);
    }
  }

#ifdef PSYS_HOM_PRINT
  fprintf(stdout ,"Q ending continuation\n");
#endif

  return point_list;
}
