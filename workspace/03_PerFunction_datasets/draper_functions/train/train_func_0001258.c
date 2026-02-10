optionsUpdate()
{
	if(type_ == Group || type_ == Profile) {
		drawGroupIcon();
	}
	else if(type_ == Contact) {
		if(!d->alerting)
			resetStatus();
		else
			resetAnim();
	}
}
