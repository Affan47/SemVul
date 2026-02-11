getNodeOrdering(const SUnit *SU) const {
    if (!SU->getNode()) return 0;

    return scheduleDAG->DAG->GetOrdering(SU->getNode());
  }
