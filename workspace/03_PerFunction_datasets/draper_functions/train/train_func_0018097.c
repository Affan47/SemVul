SetValue(const HIDData_t *pData, unsigned char *Buf, long Value)
{
	int	Weight, Bit;

	Bit = pData->Offset + 8;

	for (Weight = 0; Weight < pData->Size; Weight++, Bit++) {
		int	State = Value & (1 << Weight);

		if (State) {
			Buf[Bit >> 3] |= (1 << (Bit & 7));
		} else {
			Buf[Bit >> 3] &= ~(1 << (Bit & 7));
		}
	}
}
