dump(ScheduleDAG *DAG) const {
  LatencyPriorityQueue q = *this;
  while (!q.empty()) {
    SUnit *su = q.pop();
    dbgs() << "Height " << su->getHeight() << ": ";
    su->dump(DAG);
  }
}
