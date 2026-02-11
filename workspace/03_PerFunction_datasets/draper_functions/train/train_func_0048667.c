EmitDAGISel(RecordKeeper &RK, raw_ostream &OS) {
  DAGISelEmitter(RK).run(OS);
}
