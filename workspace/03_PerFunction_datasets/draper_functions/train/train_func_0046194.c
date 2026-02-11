soundDetectPlayer()
{

	if (QFile("/proc/asound").exists()) {
		return "aplay";
	}

	return "play";

}
