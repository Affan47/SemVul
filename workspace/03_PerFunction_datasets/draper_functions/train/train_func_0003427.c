get_eegdev_sigtype(const char* sig)
{
	int sigid;

	if (!strcmp(sig, "eeg"))
		sigid = EGD_EEG;
	else if (!strcmp(sig, "event"))
		sigid = EGD_TRIGGER;
	else
		sigid = EGD_SENSOR;

	return sigid;
}
