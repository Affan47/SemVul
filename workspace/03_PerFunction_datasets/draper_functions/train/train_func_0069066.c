onGo()
{
	delete d->jt_reg;

	d->jt_reg = new JT_Register(this);
	d->jt_reg->getForm(d->j);
	connect(d->jt_reg, SIGNAL(finished()), SLOT(getFormFinished()));
	d->jt_reg->go(false);
}
