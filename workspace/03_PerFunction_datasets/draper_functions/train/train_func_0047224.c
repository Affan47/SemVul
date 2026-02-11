voronoi_f1f2_3d(VoronoiPointData& data, const SeVec3d& p, double jitter,
				double& f1, SeVec3d& pos1,
				double& f2, SeVec3d& pos2)
    {

	SeVec3d thiscell(floor(p[0])+0.5, floor(p[1])+0.5,
			 floor(p[2])+0.5);
	f1 = f2 = std::numeric_limits<double>::max();

	SeVec3d* pos = voronoi_points(data, thiscell, jitter);
	SeVec3d* end = pos + 27;

	for (; pos != end; pos++) {
	    SeVec3d offset = *pos - p;
	    double dist = offset.dot(offset);
	    if (dist < f1) {
		f2 = f1; pos2 = pos1;
		f1 = dist;
		pos1 = *pos;
	    } else if (dist < f2) {
		f2 = dist; pos2 = *pos;
	    }
	}
	f1 = sqrt(f1); f2 = sqrt(f2);
    }
