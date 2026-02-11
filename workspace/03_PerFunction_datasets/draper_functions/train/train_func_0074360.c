ddf_EvaluateARay1(ddf_rowrange i, ddf_ConePtr cone)


{
  ddf_colrange j;
  myfloat temp,tnext;
  ddf_RayPtr Ptr, PrevPtr, TempPtr;

  ddf_init(temp); ddf_init(tnext);
  Ptr = cone->FirstRay;
  PrevPtr = cone->ArtificialRay;
  if (PrevPtr->Next != Ptr) {
    fprintf(stderr,"Error.  Artificial Ray does not point to FirstRay!!!\n");
  }
  while (Ptr != NULL) {
    ddf_set(temp,ddf_purezero);
    for (j = 0; j < cone->d; j++){
      ddf_mul(tnext,cone->A[i - 1][j],Ptr->Ray[j]);
      ddf_add(temp,temp,tnext);
    }
    ddf_set(Ptr->ARay,temp);

    if ( ddf_Negative(temp) && Ptr != cone->FirstRay) {

      if (Ptr==cone->LastRay) cone->LastRay=PrevPtr;
      TempPtr=Ptr;
      Ptr = Ptr->Next;
      PrevPtr->Next = Ptr;
      cone->ArtificialRay->Next = TempPtr;
      TempPtr->Next = cone->FirstRay;
      cone->FirstRay = TempPtr;
    }
    else {
      PrevPtr = Ptr;
      Ptr = Ptr->Next;
    }
  }
  ddf_clear(temp); ddf_clear(tnext);
}
