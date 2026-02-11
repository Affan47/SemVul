DefaultInit(void)
{
	AddMidiDevice();
	UpdateData();

	SetMidiDevice("alsa:hw:1,0");
}
