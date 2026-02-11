dInitColliders()
{
  dIASSERT(!colliders_initialized);
  colliders_initialized = 1;

  memset (colliders,0,sizeof(colliders));

  int i,j;


  for (i=dFirstSpaceClass; i <= dLastSpaceClass; i++) {
    for (j=0; j < dGeomNumClasses; j++) {
      setCollider (i,j,&dCollideSpaceGeom);
    }
  }

  setCollider (dSphereClass,dSphereClass,&dCollideSphereSphere);
  setCollider (dSphereClass,dBoxClass,&dCollideSphereBox);
  setCollider (dSphereClass,dPlaneClass,&dCollideSpherePlane);
  setCollider (dBoxClass,dBoxClass,&dCollideBoxBox);
  setCollider (dBoxClass,dPlaneClass,&dCollideBoxPlane);
  setCollider (dCapsuleClass,dSphereClass,&dCollideCapsuleSphere);
  setCollider (dCapsuleClass,dBoxClass,&dCollideCapsuleBox);
  setCollider (dCapsuleClass,dCapsuleClass,&dCollideCapsuleCapsule);
  setCollider (dCapsuleClass,dPlaneClass,&dCollideCapsulePlane);
  setCollider (dRayClass,dSphereClass,&dCollideRaySphere);
  setCollider (dRayClass,dBoxClass,&dCollideRayBox);
  setCollider (dRayClass,dCapsuleClass,&dCollideRayCapsule);
  setCollider (dRayClass,dPlaneClass,&dCollideRayPlane);
  setCollider (dRayClass,dCylinderClass,&dCollideRayCylinder);
#if dTRIMESH_ENABLED
  setCollider (dTriMeshClass,dSphereClass,&dCollideSTL);
  setCollider (dTriMeshClass,dBoxClass,&dCollideBTL);
  setCollider (dTriMeshClass,dRayClass,&dCollideRTL);
  setCollider (dTriMeshClass,dTriMeshClass,&dCollideTTL);
  setCollider (dTriMeshClass,dCapsuleClass,&dCollideCCTL);
  setCollider (dTriMeshClass,dPlaneClass,&dCollideTrimeshPlane);
  setCollider (dCylinderClass,dTriMeshClass,&dCollideCylinderTrimesh);
#endif
  setCollider (dCylinderClass,dBoxClass,&dCollideCylinderBox);
  setCollider (dCylinderClass,dSphereClass,&dCollideCylinderSphere);
  setCollider (dCylinderClass,dPlaneClass,&dCollideCylinderPlane);


  setCollider (dConvexClass,dPlaneClass,&dCollideConvexPlane);
  setCollider (dSphereClass,dConvexClass,&dCollideSphereConvex);
  setCollider (dConvexClass,dBoxClass,&dCollideConvexBox);
  setCollider (dConvexClass,dCapsuleClass,&dCollideConvexCapsule);
  setCollider (dConvexClass,dConvexClass,&dCollideConvexConvex);
  setCollider (dRayClass,dConvexClass,&dCollideRayConvex);


  setCollider (dHeightfieldClass,dRayClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dSphereClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dBoxClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dCapsuleClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dCylinderClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dConvexClass,&dCollideHeightfield);
#if dTRIMESH_ENABLED
  setCollider (dHeightfieldClass,dTriMeshClass,&dCollideHeightfield);
#endif


  setAllColliders (dGeomTransformClass,&dCollideTransform);
}
