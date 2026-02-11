set_ksl_tl(FM_OPL *OPL,int slot,int v)
{
	OPL_CH   *CH   = &OPL->P_CH[slot/2];
	OPL_SLOT *SLOT = &CH->SLOT[slot&1];
	int ksl = v>>6;

	SLOT->ksl = ksl ? 3-ksl : 31;
	SLOT->TL  = (v&0x3f)<<(ENV_BITS-1-7);

	SLOT->TLL = SLOT->TL + (CH->ksl_base>>SLOT->ksl);
}
