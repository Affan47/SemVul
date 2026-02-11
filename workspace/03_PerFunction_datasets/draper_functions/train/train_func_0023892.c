initTPObstacles(std::vector<double> &TP_Obstacles) const
{
	TP_Obstacles.resize(m_alphaValuesCount);
	for (size_t k=0;k<m_alphaValuesCount;k++)
	{
		TP_Obstacles[k] = std::min(
			refDistance,
			this->getPathDist(k, this->getPathStepCount(k)-1) );
	}
}
