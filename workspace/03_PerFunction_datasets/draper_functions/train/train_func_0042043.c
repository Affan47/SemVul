GetWidgetCount() {
	if(GetChildList() == NULL) {
		return 0;
	}

	return GetChildList()->size();
}
