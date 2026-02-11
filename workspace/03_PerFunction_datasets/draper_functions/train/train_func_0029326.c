stat(const EMIESJob& job, EMIESJobState& state) {
    XMLNode st;
    if(!stat(job,st)) return false;
    state = st;
    if(!state) {
      lfailure = "Response does not contain valid ActivityStatus";
      return false;
    };
    return true;
  }
