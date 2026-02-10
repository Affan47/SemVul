setContact(UserListItem *u)
{
	int oldStatus = d->status;
	QString oldName = text(0);
	bool wasAgent = d->isAgent;


	d->u = u;
	cacheValues();

	bool needUpdate = false;
	if(d->status != oldStatus || d->isAgent != wasAgent || !u->presenceError().isEmpty()) {
		resetStatus();
		needUpdate = true;
	}


	resetName();
	QString newName = text(0);
	if(newName != oldName) {
		needUpdate = true;
	}

	if(needUpdate)
		updatePosition();

	repaint();
	setup();
}
