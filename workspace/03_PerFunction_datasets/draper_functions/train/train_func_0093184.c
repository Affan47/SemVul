sysUpdateIcon()
{
	if ( !d )
		return;

	QPixmap pix = pm;
	d->setPixmap(pix);
}
