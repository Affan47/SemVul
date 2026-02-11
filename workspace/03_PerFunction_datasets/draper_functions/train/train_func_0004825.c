Encode(const ArrayOfUInts16 &data, int &outlen, bool &changed)
{


	int size = (int) data.size();
	if (size == 0) {
		return Encode(0, 0, outlen, changed);
	}
	CScopedArray<uint8> buf(size);
	uint8 * bufPtr = buf.get();

	for (int i = 0; i < size; i++) {
		uint16 ui = data[i];
		bufPtr[i] = (ui > 0xff) ? 0xff : (uint8) ui;
	}
	return Encode(bufPtr, size, outlen, changed);
}
