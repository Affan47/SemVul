accept()
{
	if(d->state != WaitingForAccept)
		return;

	QString dstr; dstr.sprintf("IBBConnection[%d]: accepting %s [%s]\n", d->id, d->peer.full().latin1(), d->sid.latin1());
	d->m->client()->debug(dstr);

	d->m->doAccept(this, d->iq_id);
	d->state = Active;
	d->m->link(this);
}
