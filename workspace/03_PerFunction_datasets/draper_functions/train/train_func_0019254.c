NextBit(SymbInt *simb_int)
{
	int nBit;

	nBit = (simb_int->m_pCurrent[0] & simb_int->m_ulMask) ? 1 : 0;

	if ((simb_int->m_ulMask >>= 1) == 0) {
		simb_int->m_ulMask = 0x80;

		if (simb_int->m_nUsed == simb_int->m_nSize)
			simb_int->m_pCurrent = simb_int->m_pInputBuffer;
		else {
			if (++simb_int->m_pCurrent == simb_int->m_pInputBufferEnd)
				simb_int->m_pCurrent = simb_int->m_pInputBuffer;
			simb_int->m_nUsed++;
		}
	}
	simb_int->m_ulOffset++;

	return nBit;
}
