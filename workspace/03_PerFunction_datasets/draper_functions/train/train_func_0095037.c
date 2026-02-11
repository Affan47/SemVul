overrideSchedPolicy(MachineSchedPolicy &Policy,
                                       MachineInstr *begin,
                                       MachineInstr *end,
                                       unsigned NumRegionInstrs) const {
  if (needsAggressiveScheduling(DarwinDirective)) {
    Policy.OnlyTopDown = false;
    Policy.OnlyBottomUp = false;
  }


  Policy.ShouldTrackPressure = true;
}
