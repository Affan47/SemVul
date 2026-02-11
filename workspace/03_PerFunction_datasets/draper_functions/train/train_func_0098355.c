getPortalPoints(dtPolyRef from, dtPolyRef to, float* left, float* right,
										 unsigned char& fromType, unsigned char& toType) const
{
	dtAssert(m_nav);

	const dtMeshTile* fromTile = 0;
	const dtPoly* fromPoly = 0;
	if (m_nav->getTileAndPolyByRef(from, &fromTile, &fromPoly) != DT_SUCCESS)
		return DT_FAILURE;
	fromType = fromPoly->getType();

	const dtMeshTile* toTile = 0;
	const dtPoly* toPoly = 0;
	if (m_nav->getTileAndPolyByRef(to, &toTile, &toPoly) != DT_SUCCESS)
		return DT_FAILURE;
	toType = toPoly->getType();

	return getPortalPoints(from, fromPoly, fromTile, to, toPoly, toTile, left, right);
}
