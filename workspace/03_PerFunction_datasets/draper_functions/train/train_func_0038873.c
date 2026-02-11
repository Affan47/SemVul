multiByteRead(FreeImageIO *io, fi_handle handle) {


	DWORD Out = 0;
	BYTE In = 0;

	while (io->read_proc(&In, 1, 1, handle)) {
		Out += (In & 0x7F);

		if ((In & 0x80) == 0x00)
			break;

		Out <<= 7;
	}

	return Out;
}
