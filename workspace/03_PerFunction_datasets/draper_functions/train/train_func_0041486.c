Devices_H_LoadProceed(int mydos)
{

	if (mydos) {
		switch (MEMORY_dGetByte(Devices_ICAX1Z) ) {
		case 4:
			runBinFile = TRUE;
			initBinFile = TRUE;
			break;
		case 5:
			runBinFile = TRUE;
			initBinFile = FALSE;
			break;
		case 6:
			runBinFile = FALSE;
			initBinFile = TRUE;
			break;
		case 7:
		default:
			runBinFile = FALSE;
			initBinFile = FALSE;
			break;
		}
	}
	else {
		if (MEMORY_dGetByte(Devices_ICAX2Z) < 128)
			runBinFile = TRUE;
		else
			runBinFile = FALSE;
		initBinFile = TRUE;
	}

	BINLOAD_start_binloading = TRUE;
	Devices_H_BinLoaderCont();
}
