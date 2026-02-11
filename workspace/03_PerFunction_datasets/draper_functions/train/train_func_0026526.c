fileNameFromGeneration( const char* base, const char* extension, int64_t gen ) {
		if ( gen == SegmentInfo::NO ) {
			return "";
		} else if ( gen == SegmentInfo::WITHOUT_GEN ) {
			return string(base) + extension;
		} else {
      char buf[(sizeof(unsigned long) << 3) + 1];
      CL_NS(util)::Misc::longToBase( gen, 36, buf );
      return string(base) + "_" + buf + extension;
		}
	}
