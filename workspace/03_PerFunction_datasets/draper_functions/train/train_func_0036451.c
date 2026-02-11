synchronize(bool hard = false, FileProcessor* proc = NULL,
                   ProgressChecker* checker = NULL) {
    _assert_(true);
    kc::ScopedRWLock lock(&mlock_, false);
    bool err = false;
    if (proc && !proc->process(path_, 0, 0)) {
      set_error(_KCCODELINE_, Error::LOGIC, "postprocessing failed");
      err = true;
    }
    trigger_meta(MetaTrigger::SYNCHRONIZE, "synchronize");
    return !err;
  }
