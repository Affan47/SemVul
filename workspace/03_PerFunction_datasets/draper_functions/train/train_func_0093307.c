calcSingleSpecPe(Word16 scf, Word16 sfbConstPePart, Word16 nLines)
{
	Word32 specPe;
	Word32 ldRatio;
	Word32 scf3;

	ldRatio = sfbConstPePart << 3;
	scf3 = scf + scf + scf;
	ldRatio = ldRatio - scf3;

	if (ldRatio < PE_C1_8) {

		ldRatio = (ldRatio + PE_C2_16) >> 1;
	}
	specPe = nLines * ldRatio;
	specPe = (specPe * PE_SCALE) >> 14;

	return saturate(specPe);
}
