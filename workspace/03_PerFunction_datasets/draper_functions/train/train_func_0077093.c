QuadMethods()
{
    if( !aQuadMethods ) {
	aQuadMethods = GeomClassCreate(quadName);

	aQuadMethods->name = QuadName;
        aQuadMethods->methods = (GeomMethodsFunc *)QuadMethods;
	aQuadMethods->copy = (GeomCopyFunc *)QuadCopy;
	aQuadMethods->create = (GeomCreateFunc *)QuadCreate;
        aQuadMethods->fload = (GeomFLoadFunc *)QuadFLoad;
	aQuadMethods->fsave = (GeomFSaveFunc *)QuadFSave;
	aQuadMethods->Delete = (GeomDeleteFunc *)QuadDelete;
        aQuadMethods->bound = (GeomBoundFunc *)QuadBound;
	aQuadMethods->boundsphere =
	  (GeomBoundSphereFunc *)QuadSphere;
        aQuadMethods->evert = (GeomEvertFunc *)QuadEvert;
        aQuadMethods->draw = (GeomDrawFunc *)QuadDraw;
        aQuadMethods->bsptree = (GeomBSPTreeFunc *)QuadBSPTree;
	aQuadMethods->pick = (GeomPickFunc *) QuadPick;
	aQuadMethods->transform = (GeomTransformFunc *) QuadTransform;
	aQuadMethods->transformto = (GeomTransformToFunc *) QuadTransformTo;
    }
    return aQuadMethods;
}
