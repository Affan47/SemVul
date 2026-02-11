Remove(PG_Widget* widget) {
	iterator i = find(begin(), end(), widget);

	if(i == end()) {
		return;
	}

	erase(i);
}
