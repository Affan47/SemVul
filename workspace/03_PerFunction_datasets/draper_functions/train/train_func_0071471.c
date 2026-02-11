SetVolume(float val)
{
	if (val > 2.0) {
		alsaplayer_error("ERROR: volume out of bound (%.2f)", val);
		return;
	}
	volume = val;

	std::set<coreplayer_notifier *>::const_iterator i;
	LockNotifiers();
	for (i = notifiers.begin(); i != notifiers.end(); i++) {
		if ((*i)->volume_changed)
			(*i)->volume_changed((*i)->data, volume);
	}
	UnlockNotifiers();
}
