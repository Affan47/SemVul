SetLineEndTypesAllowed(int lineEndBitSet_) {
	if (lineEndBitSet != lineEndBitSet_) {
		lineEndBitSet = lineEndBitSet_;
		int lineEndBitSetActive = lineEndBitSet & LineEndTypesSupported();
		if (lineEndBitSetActive != cb.GetLineEndTypes()) {
			ModifiedAt(0);
			cb.SetLineEndTypes(lineEndBitSetActive);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
