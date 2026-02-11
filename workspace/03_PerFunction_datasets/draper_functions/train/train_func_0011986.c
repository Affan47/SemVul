frameNumber() const
{
	if ( PsiOptions::instance()->getOption("options.ui.notifications.alert-style").toString() == "animate" && d->real->isAnimated() ) {
		return d->real->frameNumber();
	}
	else if ( PsiOptions::instance()->getOption("options.ui.notifications.alert-style").toString() == "blink" || (PsiOptions::instance()->getOption("options.ui.notifications.alert-style").toString() == "animate" && !d->real->isAnimated()) ) {
		return metaAlertIcon->framenumber();
	}

	return 0;
}
