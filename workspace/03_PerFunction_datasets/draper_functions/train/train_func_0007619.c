ListBound(List *list, Transform  T, TransformN *TN)
{
    Geom *carbox = NULL;
    BBox *bbox = NULL;
    List *l;

    for(l = list; l != NULL; l = l->cdr) {
	    carbox = GeomBound( l->car, T, TN );
	if(carbox == NULL)
		continue;
	if(bbox) {
	    BBoxUnion3(bbox, (BBox *)carbox, bbox);
	    GeomDelete( carbox );
	} else {
	    bbox = (BBox *)carbox;
	}
    }
    return bbox;
}
