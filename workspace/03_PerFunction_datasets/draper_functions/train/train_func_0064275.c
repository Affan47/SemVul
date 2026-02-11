isGuaranteedToTransferExecutionToSuccessor(const Instruction *I) {


  return !I->isAtomic() &&
         !isa<CallInst>(I) &&
         !isa<InvokeInst>(I) &&

         !isa<ResumeInst>(I) &&
         !isa<ReturnInst>(I);
}
