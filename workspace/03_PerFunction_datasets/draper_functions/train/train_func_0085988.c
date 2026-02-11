addPreRegAlloc() {
  const AMDGPUSubtarget &ST = *getAMDGPUTargetMachine().getSubtargetImpl();


  if (getOptLevel() > CodeGenOpt::None) {
    insertPass(&MachineSchedulerID, &SIFixControlFlowLiveIntervalsID);
  }

  if (getOptLevel() > CodeGenOpt::None && ST.loadStoreOptEnabled()) {


    insertPass(&MachineSchedulerID, &SILoadStoreOptimizerID);
    insertPass(&MachineSchedulerID, &RegisterCoalescerID);
  }
  addPass(createSIShrinkInstructionsPass(), false);
}
