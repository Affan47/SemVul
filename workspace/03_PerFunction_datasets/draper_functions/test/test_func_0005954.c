gimpact_vs_gimpact_find_pairs(
					  const btTransform & trans0,
					  const btTransform & trans1,
					  btGImpactShapeInterface * shape0,
					  btGImpactShapeInterface * shape1,btPairSet & pairset)
{
	if(shape0->hasBoxSet() && shape1->hasBoxSet())
	{
		btGImpactBoxSet::find_collision(shape0->getBoxSet(),trans0,shape1->getBoxSet(),trans1,pairset);
	}
	else
	{
		btAABB boxshape0;
		btAABB boxshape1;
		int i = shape0->getNumChildShapes();

		while(i--)
		{
			shape0->getChildAabb(i,trans0,boxshape0.m_min,boxshape0.m_max);

			int j = shape1->getNumChildShapes();
			while(j--)
			{
				shape1->getChildAabb(i,trans1,boxshape1.m_min,boxshape1.m_max);

				if(boxshape1.has_collision(boxshape0))
				{
					pairset.push_pair(i,j);
				}
			}
		}
	}


}
