UTF8LineEndOverlaps(int position) const {
	unsigned char bytes[] = {
		static_cast<unsigned char>(substance.ValueAt(position-2)),
		static_cast<unsigned char>(substance.ValueAt(position-1)),
		static_cast<unsigned char>(substance.ValueAt(position)),
		static_cast<unsigned char>(substance.ValueAt(position+1)),
	};
	return UTF8IsSeparator(bytes) || UTF8IsSeparator(bytes+1) || UTF8IsNEL(bytes+1);
}
