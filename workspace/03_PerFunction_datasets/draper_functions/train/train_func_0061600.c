probe_drive_range(uint8_t start)
{
    uint8_t drive = start;
    while (multi_probe_drive(drive)) {
	drive++;

	if ((drive & 0x7F) == 0)
	    break;
    }
    return drive;
}
