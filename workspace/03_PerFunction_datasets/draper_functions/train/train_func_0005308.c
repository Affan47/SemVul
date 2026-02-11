_dxfEndFace(Field f)
{
    CHECK(f, CLASS_FIELD);

    if (f->cell)
	return _EndFaceVolume(f);
    else
	return _EndFaceSurface(f);
}
