ddf_AddNewHalfspace2(ddf_ConePtr cone, ddf_rowrange hnew)

{
  ddf_RayPtr RayPtr0,RayPtr1,RayPtr2;
  ddf_AdjacencyType *EdgePtr, *EdgePtr0;
  long pos1;
  ddf_rowrange fii1, fii2;
  ddf_boolean localdebug=ddf_FALSE;

  ddf_EvaluateARay2(hnew, cone);


  if (cone->PosHead==NULL && cone->ZeroHead==NULL) {
    cone->FirstRay=NULL;
    cone->ArtificialRay->Next=cone->FirstRay;
    cone->RayCount=0;
    cone->CompStatus=ddf_AllFound;
    goto _L99;
  }

  if (localdebug){
    pos1=0;
    fprintf(stderr,"(pos, FirstInfeasIndex, A Ray)=\n");
    for (RayPtr0=cone->FirstRay; RayPtr0!=NULL; RayPtr0=RayPtr0->Next){
      pos1++;
      fprintf(stderr,"(%ld,%ld,",pos1,RayPtr0->FirstInfeasIndex);
      ddf_WriteNumber(stderr,RayPtr0->ARay);
      fprintf(stderr,") ");
   }
    fprintf(stderr,"\n");
  }

  if (cone->ZeroHead==NULL) cone->ZeroHead=cone->LastRay;

  EdgePtr=cone->Edges[cone->Iteration];
  while (EdgePtr!=NULL){
    RayPtr1=EdgePtr->Ray1;
    RayPtr2=EdgePtr->Ray2;
    fii1=RayPtr1->FirstInfeasIndex;
    ddf_CreateNewRay(cone, RayPtr1, RayPtr2, hnew);
    fii2=cone->LastRay->FirstInfeasIndex;
    if (fii1 != fii2)
      ddf_ConditionalAddEdge(cone,RayPtr1,cone->LastRay,cone->PosHead);
    EdgePtr0=EdgePtr;
    EdgePtr=EdgePtr->Next;
    free(EdgePtr0);
    (cone->EdgeCount)--;
  }
  cone->Edges[cone->Iteration]=NULL;

  ddf_DeleteNegativeRays(cone);

  set_addelem(cone->AddedHalfspaces, hnew);

  if (cone->Iteration<cone->m){
    if (cone->ZeroHead!=NULL && cone->ZeroHead!=cone->LastRay){
      if (cone->ZeroRayCount>200 && ddf_debug) fprintf(stderr,"*New edges being scanned...\n");
      ddf_UpdateEdges(cone, cone->ZeroHead, cone->LastRay);
    }
  }

  if (cone->RayCount==cone->WeaklyFeasibleRayCount) cone->CompStatus=ddf_AllFound;
_L99:;
}
