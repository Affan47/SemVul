RegisterEnvironmentForDeoptimization(LEnvironment* environment,
                                                    Safepoint::DeoptMode mode) {
  if (!environment->HasBeenRegistered()) {


    int frame_count = 0;
    for (LEnvironment* e = environment; e != NULL; e = e->outer()) {
      ++frame_count;
    }
    Translation translation(&translations_, frame_count);
    WriteTranslation(environment, &translation);
    int deoptimization_index = deoptimizations_.length();
    int pc_offset = masm()->pc_offset();
    environment->Register(deoptimization_index,
                          translation.index(),
                          (mode == Safepoint::kLazyDeopt) ? pc_offset : -1);
    deoptimizations_.Add(environment);
  }
}
