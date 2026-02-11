LoadImage(const std::string& filename) {
	DeleteThemedSurface(my_cachedSrf);
	my_cachedSrf = NULL;

	if(PG_ThemeWidget::LoadImage(filename)) {
		return true;
	}

	return false;
}
