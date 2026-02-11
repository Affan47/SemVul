start_sound(int osc, double eff_dsamps, double dsamps)
{
	register word32 start_time1;
	register word32 end_time1;
	Doc_reg	*rptr;
	int	ctl;
	int	mode;
	word32	sz;
	word32	size;
	word32	wave_size;

	if(osc < 0 || osc > 31) {
		halt_printf("start_sound: osc: %02x!\n", osc);
	}

	g_num_start_sounds++;

	rptr = &(g_doc_regs[osc]);

	if(osc >= g_doc_num_osc_en) {
		rptr->ctl |= 1;
		return;
	}

	GET_ITIMER(start_time1);

	ctl = rptr->ctl;

	mode = (ctl >> 1) & 3;

	wave_size = rptr->wavesize;

	sz = ((wave_size >> 3) & 7) + 8;
	size = 1 << sz;

	if(size < 0x100) {
		halt_printf("size: %08x is too small, sz: %08x!\n", size, sz);
	}

	if(rptr->running) {
		halt_printf("start_sound osc: %d, already running!\n", osc);
	}

	rptr->running = 1;

	rptr->complete_dsamp = eff_dsamps;

	doc_printf("Starting osc %02x, dsamp: %f\n", osc, dsamps);
	doc_printf("size: %04x\n", size);

	if((mode == 2) && ((osc & 1) == 0)) {
		printf("Sync mode osc %d starting!\n", osc);


		if((rptr[1].ctl & 7) == 5) {

			rptr[1].ctl &= (~1);
			start_sound(osc + 1, eff_dsamps, dsamps);
		} else {
			printf("Osc %d starting sync, but osc %d ctl: %02x\n",
				osc, osc+1, rptr[1].ctl);
		}
	}

	wave_end_estimate(osc, eff_dsamps, dsamps);

	DOC_LOG("st playing", osc, eff_dsamps, size);
#if 0
	if(rptr->cur_acc != 0) {
		halt_printf("Start osc %02x, acc: %08x\n", osc, rptr->cur_acc);
	}
#endif

	GET_ITIMER(end_time1);

	g_cycs_in_start_sound += (end_time1 - start_time1);
}
