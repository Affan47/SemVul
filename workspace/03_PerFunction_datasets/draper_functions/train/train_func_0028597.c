STEP3_WSpaceToTPSpace(const size_t ptg_idx,std::vector<double> &out_TPObstacles)
{
	CParameterizedTrajectoryGenerator	*ptg = this->PTGs[ptg_idx];

	const float OBS_MAX_XY = this->refDistance*1.1f;


	size_t nObs;
	const float *xs,*ys,*zs;
	m_WS_Obstacles.getPointsBuffer(nObs,xs,ys,zs);

	for (size_t obs=0;obs<nObs;obs++)
	{
		const float ox=xs[obs], oy = ys[obs], oz=zs[obs];

		if (ox>-OBS_MAX_XY && ox<OBS_MAX_XY &&
			oy>-OBS_MAX_XY && oy<OBS_MAX_XY &&
			oz>=minObstaclesHeight && oz<=maxObstaclesHeight)
		{
			ptg->updateTPObstacle(ox, oy, out_TPObstacles);
		}
	}
}
