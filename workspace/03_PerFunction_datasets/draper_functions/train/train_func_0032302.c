reset_code(unsigned char code)
{
	static char buffer[25];

	if (code == 0x00 || (code & 0x80) == 0x80)
		return "DTE Originated";
	if (code == 0x03)
		return "Remote Procedure Error";
	if (code == 0x11)
		return "Incompatible Destination";
	if (code == 0x05)
		return "Local Procedure Error";
	if (code == 0x07)
		return "Network Congestion";

	sprintf(buffer, "Unknown %02X", code);

	return buffer;
}
