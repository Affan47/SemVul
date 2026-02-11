dmac_bput2 (uaecptr addr, uae_u32 b)
{
	if (addr >= 0xb0 && addr < 0xc0) {
		tp_bput ((addr - 0xb0) / 2, b);
		return;
	}

#ifdef CDTV_DEBUG
	write_log (_T("dmac_bput %04X=%02X PC=%08X\n"), addr, b & 255, M68K_GETPC);
#endif

	switch (addr)
	{
	case 0x43:
		dmac_cntr = b;
		if (dmac_cntr & CNTR_PREST)
			cdtv_reset_int ();
		break;
	case 0x80:
		dmac_wtc &= 0x00ffffff;
		dmac_wtc |= b << 24;
		break;
	case 0x81:
		dmac_wtc &= 0xff00ffff;
		dmac_wtc |= b << 16;
		break;
	case 0x82:
		dmac_wtc &= 0xffff00ff;
		dmac_wtc |= b << 8;
		break;
	case 0x83:
		dmac_wtc &= 0xffffff00;
		dmac_wtc |= b << 0;
		break;
	case 0x84:
		dmac_acr &= 0x00ffffff;
		dmac_acr |= b << 24;
		break;
	case 0x85:
		dmac_acr &= 0xff00ffff;
		dmac_acr |= b << 16;
		break;
	case 0x86:
		dmac_acr &= 0xffff00ff;
		dmac_acr |= b << 8;
		break;
	case 0x87:
		dmac_acr &= 0xffffff01;
		dmac_acr |= (b & ~ 1) << 0;
		break;
	case 0x8e:
		dmac_dawr &= 0x00ff;
		dmac_dawr |= b << 8;
		break;
	case 0x8f:
		dmac_dawr &= 0xff00;
		dmac_dawr |= b << 0;
		break;
	case 0x91:
		if (currprefs.cs_cdtvscsi) {
			wdscsi_sasr (b);
			checkint ();
		}
		break;
	case 0x93:
		if (currprefs.cs_cdtvscsi) {
			wdscsi_put (b);
			checkint ();
		}
		break;
	case 0xa1:
		cdrom_command (b);
		break;
	case 0xe0:
	case 0xe1:
		if (!dmac_dma) {
			dmac_dma = 1;
			dmac_start_dma ();
		}
		break;
	case 0xe2:
	case 0xe3:
		dmac_dma = 0;
		dma_finished = 0;
		break;
	case 0xe4:
	case 0xe5:
		dmac_istr = 0;
		checkint ();
		break;
	case 0xe8:
	case 0xe9:
		dmac_istr |= ISTR_FE_FLG;
		break;
	}

	tp_check_interrupts ();
}
