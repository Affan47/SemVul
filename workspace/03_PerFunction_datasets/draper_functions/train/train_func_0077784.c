generate3DObject(TObject3D &obj) const	{
	switch (type)	{
		case GEOMETRIC_TYPE_POINT:
			obj=TPoint3D(data.point);
			break;
		case GEOMETRIC_TYPE_SEGMENT:
			obj=TSegment3D(data.segment);
			break;
		case GEOMETRIC_TYPE_LINE:
			obj=TLine3D(data.line);
			break;
		case GEOMETRIC_TYPE_POLYGON:
			obj=TPolygon3D(*(data.polygon));
			break;
		default:
			obj=TObject3D();
			break;
	}
}
