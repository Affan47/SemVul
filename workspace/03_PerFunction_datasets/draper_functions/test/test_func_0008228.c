getAttributeAsTriangle3d(s32 index)
{
	core::triangle3df ret;
	ret.pointA = ret.pointB = ret.pointC = core::vector3df(0,0,0);

	if (index >= 0 && index < (s32)Attributes.size())
		ret = Attributes[index]->getTriangle();

	return ret;
}
