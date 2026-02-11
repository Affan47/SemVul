chooseStatusPreset(int x)
{
	if(x < 1)
		return;

	QString base = PsiOptions::instance()->mapLookup("options.status.presets", d->cb_preset->text(x));
	d->te->setText(PsiOptions::instance()->getOption(base+".message").toString());
	if (PsiOptions::instance()->getOption(base+".force-priority").toBool()) {
		d->le_priority->setText(QString::number(PsiOptions::instance()->getOption(base+".priority").toInt()));
	} else {
		d->le_priority->clear();
	}

	XMPP::Status status;
	status.setType(PsiOptions::instance()->getOption(base+".status").toString());
	d->cb_type->setStatus(status.type());
}
