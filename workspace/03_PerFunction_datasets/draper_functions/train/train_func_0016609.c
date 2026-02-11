getOrigin(CPolyhedronPtr &poly) const	{
	if (!meshUpToDate) updateMesh();
	if (axis.size()<2||generatrix.size()<3) throw std::logic_error("Not enough points.");
	size_t i=fullyVisible?0:firstSection;
	generatePolygon(poly,generatrix,axis[i]);
	poly->setPose(this->m_pose);
	poly->setColor(getColor());
}
