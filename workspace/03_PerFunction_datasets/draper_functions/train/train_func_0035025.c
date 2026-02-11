check_engine_asm_defines()
{
	Fplus	fplus;
	Fplus	*fplusptr;
	Pc_log	pclog;
	Pc_log	*pcptr;
	Engine_reg ereg;
	Engine_reg *eptr;
	word32	val1;
	word32	val2;

	eptr = &ereg;
	CHECK(eptr, eptr->fcycles, ENGINE_FCYCLES, val1, val2);
	CHECK(eptr, eptr->fplus_ptr, ENGINE_FPLUS_PTR, val1, val2);
	CHECK(eptr, eptr->acc, ENGINE_REG_ACC, val1, val2);
	CHECK(eptr, eptr->xreg, ENGINE_REG_XREG, val1, val2);
	CHECK(eptr, eptr->yreg, ENGINE_REG_YREG, val1, val2);
	CHECK(eptr, eptr->stack, ENGINE_REG_STACK, val1, val2);
	CHECK(eptr, eptr->dbank, ENGINE_REG_DBANK, val1, val2);
	CHECK(eptr, eptr->direct, ENGINE_REG_DIRECT, val1, val2);
	CHECK(eptr, eptr->psr, ENGINE_REG_PSR, val1, val2);
	CHECK(eptr, eptr->kpc, ENGINE_REG_KPC, val1, val2);

	pcptr = &pclog;
	CHECK(pcptr, pcptr->dbank_kpc, LOG_PC_DBANK_KPC, val1, val2);
	CHECK(pcptr, pcptr->instr, LOG_PC_INSTR, val1, val2);
	CHECK(pcptr, pcptr->psr_acc, LOG_PC_PSR_ACC, val1, val2);
	CHECK(pcptr, pcptr->xreg_yreg, LOG_PC_XREG_YREG, val1, val2);
	CHECK(pcptr, pcptr->stack_direct, LOG_PC_STACK_DIRECT, val1, val2);
	if(LOG_PC_SIZE != sizeof(pclog)) {
		printf("LOG_PC_SIZE: %d != sizeof=%d\n", LOG_PC_SIZE,
			(int)sizeof(pclog));
		exit(2);
	}

	fplusptr = &fplus;
	CHECK(fplusptr, fplusptr->plus_1, FPLUS_PLUS_1, val1, val2);
	CHECK(fplusptr, fplusptr->plus_2, FPLUS_PLUS_2, val1, val2);
	CHECK(fplusptr, fplusptr->plus_3, FPLUS_PLUS_3, val1, val2);
	CHECK(fplusptr, fplusptr->plus_x_minus_1, FPLUS_PLUS_X_M1, val1, val2);
}
