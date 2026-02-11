clear() {
			Path::clear();
			base = "";
			extension = "";
			if (ifs != nullptr) {
				delete ifs;
				ifs=nullptr;
			}
		}
