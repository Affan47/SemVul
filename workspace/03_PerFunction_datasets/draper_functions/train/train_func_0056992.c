print_devices (AuServer *aud)
{

    int i;

    for (i = 0; i < AuServerNumDevices(aud); i++) {
	printf ("%sDevice %d:\n", INDENTPAD, i);
	print_device (aud, AuServerDevice(aud,i));
    }
}
