mouse2world(Point *axis, int objid)
{
    Transform C2W, T, Tinv;
    DObject *dobj;

    if((dobj = drawer_get_object(objid)) == NULL)
	return;

    CamGet( dview[uistate.mousefocus]->cam, CAM_C2W, C2W );
    PtTransform( C2W, axis, axis );

    if(ISCAM(objid)) {
	CamGet( ((DView *)dobj)->cam, CAM_W2C, Tinv );
	PtTransform( Tinv, axis, axis );
    } else if(((DGeom *)dobj)->citizenship == ORDINARY) {
	GeomGet(dgeom[0]->Item, CR_AXIS, T);

	TmInvert(T, Tinv);
	PtTransform( Tinv, axis, axis );
    }
}
