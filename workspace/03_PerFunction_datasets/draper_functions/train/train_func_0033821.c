do_wdm(word32 arg)
{
	switch(arg) {
	case 0x8d:
		break;
	default:
		halt_printf("do_wdm: %02x!\n", arg);
	}
}
