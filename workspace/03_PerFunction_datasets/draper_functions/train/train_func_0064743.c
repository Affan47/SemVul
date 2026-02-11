ddf_DDMain(ddf_ConePtr cone)
{
  ddf_rowrange hh, itemp, otemp;
  ddf_boolean locallog=ddf_log;

  if (cone->d<=0){
    cone->Iteration=cone->m;
    cone->FeasibleRayCount=0;
    cone->CompStatus=ddf_AllFound;
    goto _L99;
  }
  if (locallog) {
     fprintf(stderr,"(Initially added rows ) = ");
     set_fwrite(stderr,cone->InitialHalfspaces);
  }
  while (cone->Iteration <= cone->m) {
    ddf_SelectNextHalfspace(cone, cone->WeaklyAddedHalfspaces, &hh);
    if (set_member(hh,cone->NonequalitySet)){
      if (ddf_debug) {
        fprintf(stderr,"*The row # %3ld should be inactive and thus skipped.\n", hh);
      }
      set_addelem(cone->WeaklyAddedHalfspaces, hh);
    } else {
      if (cone->PreOrderedRun)
        ddf_AddNewHalfspace2(cone, hh);
      else{
        ddf_AddNewHalfspace1(cone, hh);
      }
      set_addelem(cone->AddedHalfspaces, hh);
      set_addelem(cone->WeaklyAddedHalfspaces, hh);
    }
    if (!cone->PreOrderedRun){
      for (itemp=1; cone->OrderVector[itemp]!=hh; itemp++);
        otemp=cone->OrderVector[cone->Iteration];
      cone->OrderVector[cone->Iteration]=hh;

      cone->OrderVector[itemp]=otemp;

    }
    if (locallog){
      fprintf(stderr,"(Iter, Row, #Total, #Curr, #Feas)= %5ld %5ld %9ld %6ld %6ld\n",
        cone->Iteration, hh, cone->TotalRayCount, cone->RayCount,
        cone->FeasibleRayCount);
    }
    if (cone->CompStatus==ddf_AllFound||cone->CompStatus==ddf_RegionEmpty) {
      set_addelem(cone->AddedHalfspaces, hh);
      goto _L99;
    }
    (cone->Iteration)++;
  }
  _L99:;
  if (cone->d<=0 || cone->newcol[1]==0){
     cone->parent->n=cone->LinearityDim + cone->FeasibleRayCount -1;
     cone->parent->ldim=cone->LinearityDim - 1;
  } else {
    cone->parent->n=cone->LinearityDim + cone->FeasibleRayCount;
    cone->parent->ldim=cone->LinearityDim;
  }
}
