currentPage() {
	if (currentPageIndex() == -1)
		return 0;
	return widgets_[currentPageIndex()];
}
