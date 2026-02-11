setEnabled(bool e)
{
	d->v_enabled = e;
	if(d->v_enabled){
		if(!d->cvi)
			d->cvi = new ContactViewItem(d->name, this, d->cv);
		addAllNeededContactItems();
	}
	else{
		if(d->self)
			removeSelf();

		removeAllUnneededContactItems();
		if(d->cvi)
			delete d->cvi;
		d->cvi = 0;
		d->self = 0;
	}
}
