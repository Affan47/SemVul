operator()(const GLEFileLocation& s1, const GLEFileLocation& s2) const {
		if (s1.getExt() == s2.getExt()) {
			if (s1.getName() == s2.getName()) {
				return s1.getFullPath() < s2.getFullPath();
			} else {
				return s1.getName() < s2.getName();
			}
		} else {
			if (str_i_equals(s1.getExt(), "GLE")) return true;
			if (str_i_equals(s2.getExt(), "GLE")) return false;
			return s1.getExt() < s2.getExt();
		}
	}
}
