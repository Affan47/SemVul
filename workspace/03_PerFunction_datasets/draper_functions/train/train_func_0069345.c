STEP3_WSpaceToTPSpace(
	const size_t ptg_idx,
	std::vector<double> &out_TPObstacles )
{
	ASSERT_EQUAL_(m_WS_Obstacles_inlevels.size(),m_robotShape.size())

	for (size_t j=0;j<m_robotShape.size();j++)
	{
		size_t nObs;
		const float *xs,*ys,*zs;
		m_WS_Obstacles_inlevels[j].getPointsBuffer(nObs,xs,ys,zs);

		for (size_t obs=0;obs<nObs;obs++)
		{
			const float ox = xs[obs], oy = ys[obs];
			m_ptgmultilevel[ptg_idx].PTGs[j]->updateTPObstacle(ox, oy, out_TPObstacles);
		}
	}


}
