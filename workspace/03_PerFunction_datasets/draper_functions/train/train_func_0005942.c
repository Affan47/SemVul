calculateSchedDataNVC0(const Target *targ, Function *func)
{
   SchedDataCalculator sched(targ);
   return sched.run(func, true, true);
}
