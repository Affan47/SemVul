fiji_populate_memory_timing_parameters(struct pp_hwmgr *hwmgr,
		int32_t eng_clock, int32_t mem_clock,
		struct SMU73_Discrete_MCArbDramTimingTableEntry *arb_regs)
{
	uint32_t dram_timing;
	uint32_t dram_timing2;
	uint32_t burstTime;
	ULONG state, trrds, trrdl;
	int result;

	result = atomctrl_set_engine_dram_timings_rv770(hwmgr,
			eng_clock, mem_clock);
	PP_ASSERT_WITH_CODE(result == 0,
			"Error calling VBIOS to set DRAM_TIMING.", return result);

	dram_timing = cgs_read_register(hwmgr->device, mmMC_ARB_DRAM_TIMING);
	dram_timing2 = cgs_read_register(hwmgr->device, mmMC_ARB_DRAM_TIMING2);
	burstTime = cgs_read_register(hwmgr->device, mmMC_ARB_BURST_TIME);

	state = PHM_GET_FIELD(burstTime, MC_ARB_BURST_TIME, STATE0);
	trrds = PHM_GET_FIELD(burstTime, MC_ARB_BURST_TIME, TRRDS0);
	trrdl = PHM_GET_FIELD(burstTime, MC_ARB_BURST_TIME, TRRDL0);

	arb_regs->McArbDramTiming  = PP_HOST_TO_SMC_UL(dram_timing);
	arb_regs->McArbDramTiming2 = PP_HOST_TO_SMC_UL(dram_timing2);
	arb_regs->McArbBurstTime   = (uint8_t)burstTime;
	arb_regs->TRRDS            = (uint8_t)trrds;
	arb_regs->TRRDL            = (uint8_t)trrdl;

	return 0;
}
