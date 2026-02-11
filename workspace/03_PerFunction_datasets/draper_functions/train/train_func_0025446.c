ensureVisible(Entry *e)
{
	if(!e->alerting) {
		if(!d->cv->isShowAgents() && e->u.isTransport())
			d->cv->setShowAgents(true);
		if(!d->cv->isShowOffline() && !e->u.isAvailable())
			d->cv->setShowOffline(true);
		if(!d->cv->isShowAway() && e->u.isAway())
			d->cv->setShowAway(true);
		if(!d->cv->isShowHidden() && e->u.isHidden())
			d->cv->setShowHidden(true);
	}

	ContactViewItem *i = e->cvi.first();
	if(!i)
		return;
	d->cv->ensureItemVisible(i);
}
