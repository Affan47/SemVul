reset(SharedContext* a_ctx) {
		clearQueue();
		syncT.reset();
		workSem.unsafe_init(0, a_ctx ? a_ctx->numSolvers() : 0);
		globalR     = ScheduleStrategy::none();
		maxConflict = globalR.current();
		ctx         = a_ctx;
		path        = 0;
		nextId      = 1;
		workReq     = 0;
		restartReq  = 0;
		control     = 0;
	}
