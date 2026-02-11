_calc_splitting_axis(
	gim_array<GIM_AABB_DATA> & primitive_boxes, GUINT startIndex,  GUINT endIndex)
{
	GUINT i;

	btVector3 means(btScalar(0.),btScalar(0.),btScalar(0.));
	btVector3 variance(btScalar(0.),btScalar(0.),btScalar(0.));
	GUINT numIndices = endIndex-startIndex;

	for (i=startIndex;i<endIndex;i++)
	{
		btVector3 center = btScalar(0.5)*(primitive_boxes[i].m_bound.m_max +
					 primitive_boxes[i].m_bound.m_min);
		means+=center;
	}
	means *= (btScalar(1.)/(btScalar)numIndices);

	for (i=startIndex;i<endIndex;i++)
	{
		btVector3 center = btScalar(0.5)*(primitive_boxes[i].m_bound.m_max +
					 primitive_boxes[i].m_bound.m_min);
		btVector3 diff2 = center-means;
		diff2 = diff2 * diff2;
		variance += diff2;
	}
	variance *= (btScalar(1.)/	((btScalar)numIndices-1)	);

	return variance.maxAxis();
}
