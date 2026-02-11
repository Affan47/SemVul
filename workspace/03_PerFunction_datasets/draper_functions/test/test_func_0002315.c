CornerXYZ(float scale)
{
	CSetOfObjectsPtr ret = CSetOfObjects::Create();

	CArrowPtr obj = CArrow::Create(
			0,0,0,
			scale,0,0,
			0.25f*scale,0.02f*scale,0.05f*scale);

	obj->setColor(1,0,0);

	ret->insert( obj );

	obj = CArrow::Create(
			0,0,0,
			0,scale,0,
			0.25f*scale,0.02f*scale,0.05f*scale);
	obj->setColor(0,1,0);

	ret->insert( obj );

	obj = CArrow::Create(
		0,0,0,
		0,0,scale,
		0.25f*scale,0.02f*scale,0.05f*scale);
	obj->setColor(0,0,1);

	ret->insert( obj );

	return ret;
}
