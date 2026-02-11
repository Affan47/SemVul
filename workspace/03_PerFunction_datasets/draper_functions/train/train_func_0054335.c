selectedIndex() {
	int idx = 0;
	foreach(QGraphicsItem *it, scene()->items()) {
		SvgIconWidget *icon = dynamic_cast<SvgIconWidget*>(it);
		if(icon) {
			if(icon->isSelected()) {
				return idx;
			} else {
				idx++;
			}
		}
	}
	return -1;
}
