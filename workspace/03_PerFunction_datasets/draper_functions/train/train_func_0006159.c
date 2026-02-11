dCollideBTL(dxGeom* g1, dxGeom* BoxGeom, int Flags, dContactGeom* Contacts, int Stride){
  dIASSERT (Stride >= (int)sizeof(dContactGeom));
  dIASSERT (g1->type == dTriMeshClass);
  dIASSERT (BoxGeom->type == dBoxClass);
  dIASSERT ((Flags & NUMC_MASK) >= 1);

  dxTriMesh* TriMesh = (dxTriMesh*)g1;

  sTrimeshBoxColliderData cData;
  cData.SetupInitialContext(TriMesh, BoxGeom, Flags, Contacts, Stride);

  const unsigned uiTLSKind = TriMesh->getParentSpaceTLSKind();
  dIASSERT(uiTLSKind == BoxGeom->getParentSpaceTLSKind());
  TrimeshCollidersCache *pccColliderCache = GetTrimeshCollidersCache(uiTLSKind);
  OBBCollider& Collider = pccColliderCache->_OBBCollider;

  dQueryBTLPotentialCollisionTriangles(Collider, cData, TriMesh, BoxGeom,
    pccColliderCache->defaultBoxCache);

  if (!Collider.GetContactStatus()) {

  	return 0;
  }


  int TriCount = Collider.GetNbTouchedPrimitives();
  const int* Triangles = (const int*)Collider.GetTouchedPrimitives();

  if (TriCount != 0){
      if (TriMesh->ArrayCallback != null){
         TriMesh->ArrayCallback(TriMesh, BoxGeom, Triangles, TriCount);
    }


    const dMatrix3& mRotMesh=*(const dMatrix3*)dGeomGetRotation(TriMesh);
    const dVector3& vPosMesh=*(const dVector3*)dGeomGetPosition(TriMesh);

    int ctContacts0 = 0;


    for (int i = 0; i < TriCount; i++){
        const int Triint = Triangles[i];
        if (!Callback(TriMesh, BoxGeom, Triint)) continue;

        dVector3 dv[3];
		FetchTriangle(TriMesh, Triint, vPosMesh, mRotMesh, dv);

		bool bFinishSearching;
		ctContacts0 = cData.TestCollisionForSingleTriangle(ctContacts0, Triint, dv, bFinishSearching);

		if (bFinishSearching) {
			break;
		}
	}
  }

  return cData.m_ctContacts;
}
