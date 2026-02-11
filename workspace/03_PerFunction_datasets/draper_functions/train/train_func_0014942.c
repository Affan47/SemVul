dGeomTriMeshDataGet(dTriMeshDataID g, int data_id)
{
    dUASSERT(g, "argument not trimesh data");

    switch (data_id)
	{
    case TRIMESH_FACE_NORMALS:
        return (void *) g->Normals;
        break;

	default:
        dUASSERT(data_id, "invalid data type");
        break;
    }

    return NULL;
}
