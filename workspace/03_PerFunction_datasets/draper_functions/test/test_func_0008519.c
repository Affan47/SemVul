dGeomTriMeshIsTCEnabled(dGeomID g, int geomClass)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");

	switch (geomClass)
	{
		case dSphereClass:
			if (((dxTriMesh*)g)->doSphereTC)
				return 1;
			break;
		case dBoxClass:
			if (((dxTriMesh*)g)->doBoxTC)
				return 1;
			break;
		case dCapsuleClass:
			if (((dxTriMesh*)g)->doCapsuleTC)
				return 1;
			break;
	}
	return 0;
}
