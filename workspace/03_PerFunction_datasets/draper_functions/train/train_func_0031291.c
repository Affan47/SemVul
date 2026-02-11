kmVec3Normalize(kmVec3* pOut, const kmVec3* pIn)
{
        if (!pIn->x && !pIn->y && !pIn->z)
                return kmVec3Assign(pOut, pIn);

        kmScalar l = 1.0f / kmVec3Length(pIn);

	kmVec3 v;
	v.x = pIn->x * l;
	v.y = pIn->y * l;
	v.z = pIn->z * l;

	pOut->x = v.x;
	pOut->y = v.y;
	pOut->z = v.z;

	return pOut;
}
