PG_WidgetDnD(PG_Widget* parent, int dndID, const PG_Rect& r) :
		PG_Widget(parent, r, false),
		CanDrag(true),
		CanDrop(true),
		Draging(false),
		dragimage(NULL),
dragimagecache(NULL) {
	SetID(dndID);


	dnd_next = dnd_objectlist;
	dnd_objectlist = this;
}
