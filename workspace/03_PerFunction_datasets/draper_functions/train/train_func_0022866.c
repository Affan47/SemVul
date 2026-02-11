bufferFixedPrecision(const PrecisionModel& fixedPM)
{


	PrecisionModel pm(1.0);

#if 0
  snapround::MCIndexSnapRounder inoder(pm);
#else
  algorithm::LineIntersector li(&fixedPM);
  IntersectionAdder ia(li);
  MCIndexNoder inoder(&ia);
#endif

	ScaledNoder noder(inoder, fixedPM.getScale());

	BufferBuilder bufBuilder(bufParams);
	bufBuilder.setWorkingPrecisionModel(&fixedPM);

	bufBuilder.setNoder(&noder);


	const Geometry *workGeom = argGeom;
	const PrecisionModel& argPM = *(argGeom->getFactory()->getPrecisionModel());
	std::auto_ptr<Geometry> fixedGeom;
	if ( argPM.getType() != PrecisionModel::FIXED || argPM.getScale() != fixedPM.getScale() )
	{
		using precision::GeometryPrecisionReducer;
		fixedGeom = GeometryPrecisionReducer::reduce(*argGeom, fixedPM);
		workGeom = fixedGeom.get();
	}


	resultGeometry = bufBuilder.buffer(workGeom, distance);
}
