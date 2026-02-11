insertIndividualPoint(const double x,const double y,const double z, const CHeightGridMap2D_Base::TPointInsertParams & params)
{
	const TRandomFieldCell *cell = cellByPos(x,y);
	if (!cell) return false;

	MRPT_TODO("insertIndividualPoint: allow different std values")
	if (params.pt_z_std!=0.0)
		throw std::runtime_error("CHeightGridMap2D_MRF::insertIndividualPoint() point variable variance not implemented yet!");

	this->insertIndividualReading(z, mrpt::math::TPoint2D(x,y), params.update_map_after_insertion );
	return true;
}
