encode(string &in)
{
	size_t n;
	byte igroup[7], ogroup[8];
	char insize[20];
	snprintf(insize, sizeof(insize), "%d\n", in.length());

	output.assign(insize);
	iocp = 0;
	ateof = false;

	iolen = in.length();
	string temp;
	while (!ateof) {
		igroup[0] = igroup[1] = igroup[2] =
		igroup[3] = igroup[4] = igroup[5] = igroup[6] = 0;
		for (n = 0; n < 7; n++) {
			if (iocp == iolen) {
				ateof = true;
				break;
			}
			igroup[n] = (byte)in[iocp];
			iocp++;
		}
		if (n > 0) {
			ogroup[0] =                              (igroup[0] >> 1) & 0x7F;
			ogroup[1] = ((igroup[0] << 6) & 0x40) | ((igroup[1] >> 2) & 0x3F);
			ogroup[2] = ((igroup[1] << 5) & 0x60) | ((igroup[2] >> 3) & 0x1F);
			ogroup[3] = ((igroup[2] << 4) & 0x70) | ((igroup[3] >> 4) & 0x0F);
			ogroup[4] = ((igroup[3] << 3) & 0x78) | ((igroup[4] >> 5) & 0x07);
			ogroup[5] = ((igroup[4] << 2) & 0x7C) | ((igroup[5] >> 6) & 0x03);
			ogroup[6] = ((igroup[5] << 1) & 0x7E) | ((igroup[6] >> 7) & 0x01);
			ogroup[7] =  (igroup[6]       & 0x7F);

			for (int i = 0; i < 8; i++) temp += (byte)ogroup[i];
		}
	}
	escape (temp);
	addlf(temp);
	output.append(temp);
	return output;
}
