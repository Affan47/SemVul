ddf_AddRay(ddf_ConePtr cone, myfloat *p)
{
  ddf_boolean feasible, weaklyfeasible;
  ddf_colrange j;

  if (cone->FirstRay == NULL) {
    cone->FirstRay = (ddf_RayPtr) malloc(sizeof(ddf_RayType));
    cone->FirstRay->Ray = (myfloat *) calloc(cone->d, sizeof(myfloat));
    for (j=0; j<cone->d; j++) ddf_init(cone->FirstRay->Ray[j]);
    ddf_init(cone->FirstRay->ARay);
    if (ddf_debug)
      fprintf(stderr,"Create the first ray pointer\n");
    cone->LastRay = cone->FirstRay;
    cone->ArtificialRay->Next = cone->FirstRay;
  } else {
    cone->LastRay->Next = (ddf_RayPtr) malloc(sizeof(ddf_RayType));
    cone->LastRay->Next->Ray = (myfloat *) calloc(cone->d, sizeof(myfloat));
    for (j=0; j<cone->d; j++) ddf_init(cone->LastRay->Next->Ray[j]);
    ddf_init(cone->LastRay->Next->ARay);
    if (ddf_debug) fprintf(stderr,"Create a new ray pointer\n");
    cone->LastRay = cone->LastRay->Next;
  }
  cone->LastRay->Next = NULL;
  cone->RayCount++;
  cone->TotalRayCount++;
  if (ddf_debug) {
    if (cone->TotalRayCount % 100 == 0) {
      fprintf(stderr,"*Rays (Total, Currently Active, Feasible) =%8ld%8ld%8ld\n",
	 cone->TotalRayCount, cone->RayCount, cone->FeasibleRayCount);
    }
  }
  if (cone->parent->RelaxedEnumeration){
    ddf_StoreRay2(cone, p, &feasible, &weaklyfeasible);
    if (weaklyfeasible) (cone->WeaklyFeasibleRayCount)++;
  } else {
    ddf_StoreRay1(cone, p, &feasible);
    if (feasible) (cone->WeaklyFeasibleRayCount)++;

  }
  if (!feasible) return;
  else {
    (cone->FeasibleRayCount)++;
  }
}
