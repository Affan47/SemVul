operator=(const VCard &from)
{
	if(d->agent) {
		delete d->agent;
		d->agent = 0;
	}

	*d = *from.d;

	if(from.d->agent) {

		d->agent = new VCard(*from.d->agent);
	}

	return *this;
}
