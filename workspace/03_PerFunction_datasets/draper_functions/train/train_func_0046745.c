setControl(uint8 value)
{
	control = value & 0x0f;
	if (value & 0x10)
		state = false;

}
