snd_trident_enable_eso(struct snd_trident * trident)
{
	unsigned int val;

	val = inl(TRID_REG(trident, T4D_LFO_GC_CIR));
	val |= ENDLP_IE;
	val |= MIDLP_IE;
	if (trident->device == TRIDENT_DEVICE_ID_SI7018)
		val |= BANK_B_EN;
	outl(val, TRID_REG(trident, T4D_LFO_GC_CIR));
}
