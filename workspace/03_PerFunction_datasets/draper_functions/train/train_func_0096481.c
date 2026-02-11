GetBoundingBox(const ClipperLib::Polygon& poly)
{
	IfcVector2 newbb_min, newbb_max;
	MinMaxChooser<IfcVector2>()(newbb_min, newbb_max);

	BOOST_FOREACH(const ClipperLib::IntPoint& point, poly) {
		IfcVector2 vv = IfcVector2( from_int64(point.X), from_int64(point.Y));


		vv = std::max(vv,IfcVector2());
		vv = std::min(vv,one_vec);

		newbb_min = std::min(newbb_min,vv);
		newbb_max = std::max(newbb_max,vv);
	}
	return BoundingBox(newbb_min, newbb_max);
}
