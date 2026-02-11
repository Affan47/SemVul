BezierBSPTree(Bezier *bezier, BSPTree *bsptree, int action)
{
    if (never_translucent((Geom *)bezier)) {
	return bezier;
    }

    switch (action) {
    case BSPTREE_CREATE:
	HandleRegister(&bezier->meshhandle,
		       (Ref *)bezier, bsptree, BSPTreeInvalidate);
	return bezier;
    case BSPTREE_DELETE:
	HandleUnregisterJust(&bezier->meshhandle,
			     (Ref *)bezier, bsptree,BSPTreeInvalidate);
	return bezier;
    case BSPTREE_ADDGEOM:
	if (bezier->mesh == NULL ||
	    bezier->mesh->nu != bezier->nu || bezier->mesh->nv != bezier->nv) {
	    bezier->geomflags |= BEZ_REMESH;
	}
	if (bezier->geomflags & BEZ_REMESH) {
	    BezierReDice(bezier);
	}
	BSPTreeAddObject(bsptree, (Geom *)bezier->mesh);
	return bezier;
    default:
	return NULL;
    }
}
