turnOffTransducers()
{

	if (sendSetMask(0, 0)) {
		ArLog::log (ArLog::Normal,
	              "%s::turnOffTransducers() turning OFF transducers",
	              getNameWithBoard());
		myTransducersAreOn = false;
		return true;

	}
	else {
		ArLog::log (ArLog::Normal,
	              "%s::turnOnTransducers() failed turning OFF transducers",
	              getNameWithBoard());
		return false;

	}

}
