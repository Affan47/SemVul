CleanupOuterContour(const std::vector<IfcVector2>& contour_flat, TempMesh& curmesh)
{
	std::vector<IfcVector3> vold;
	std::vector<unsigned int> iold;

	vold.reserve(curmesh.verts.size());
	iold.reserve(curmesh.vertcnt.size());


	try {

		ClipperLib::Polygon subject;
		ClipperLib::Clipper clipper;
		ClipperLib::ExPolygons clipped;

		ClipperLib::Polygon clip;
		clip.reserve(contour_flat.size());
		BOOST_FOREACH(const IfcVector2& pip, contour_flat) {
			clip.push_back(ClipperLib::IntPoint(  to_int64(pip.x), to_int64(pip.y) ));
		}

		if (!ClipperLib::Orientation(clip)) {
			std::reverse(clip.begin(), clip.end());
		}


		subject.reserve(4);
		size_t index = 0;
		size_t countdown = 0;
		BOOST_FOREACH(const IfcVector3& pip, curmesh.verts) {
			if (!countdown) {
				countdown = curmesh.vertcnt[index++];
				if (!countdown) {
					continue;
				}
			}
			subject.push_back(ClipperLib::IntPoint(  to_int64(pip.x), to_int64(pip.y) ));
			if (--countdown == 0) {
				if (!ClipperLib::Orientation(subject)) {
					std::reverse(subject.begin(), subject.end());
				}

				clipper.AddPolygon(subject,ClipperLib::ptSubject);
				clipper.AddPolygon(clip,ClipperLib::ptClip);

				clipper.Execute(ClipperLib::ctIntersection,clipped,ClipperLib::pftNonZero,ClipperLib::pftNonZero);

				BOOST_FOREACH(const ClipperLib::ExPolygon& ex, clipped) {
					iold.push_back(ex.outer.size());
					BOOST_FOREACH(const ClipperLib::IntPoint& point, ex.outer) {
						vold.push_back(IfcVector3(
							from_int64(point.X),
							from_int64(point.Y),
							0.0f));
					}
				}

				subject.clear();
				clipped.clear();
				clipper.Clear();
			}
		}
	}
	catch (const char* sx) {
		IFCImporter::LogError("Ifc: error during polygon clipping, wall contour line may be wrong: (Clipper: "
			+ std::string(sx) + ")");

		return;
	}


	std::swap(vold,curmesh.verts);
	std::swap(iold,curmesh.vertcnt);
}
