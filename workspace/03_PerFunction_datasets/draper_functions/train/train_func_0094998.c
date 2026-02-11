resetAnim()
{
	for(Q3ListViewItemIterator it(this); it.current() ; ++it) {
		ContactViewItem *item = (ContactViewItem *)it.current();
		if(item->isAlerting())
			item->resetAnim();
	}
}
