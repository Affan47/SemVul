known(KnownFonts* old_k, const UniqueString& name) {
    if (old_k != nil) {
	return old_k;
    }
    KnownFonts* k = new KnownFonts;
    fonts_->insert(name, k);
    return k;
}
