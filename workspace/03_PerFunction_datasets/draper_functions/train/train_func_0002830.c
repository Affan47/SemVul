Rate(const std::string& r) const {


		if (r == "SolidModel") {
			return -3;
		}


		if (r == "SweptSolid") {
			return -10;
		}

		if (r == "Clipping") {
			return -5;
		}


		if (r == "Brep") {
			return -2;
		}


		if (r == "BoundingBox" || r == "Curve2D") {
			return 100;
		}
		return 0;
	}
