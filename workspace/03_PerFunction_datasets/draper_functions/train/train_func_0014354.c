Submit(const ExecutionTarget& et, const std::list<JobDescription>& descs) {
    ClearAll();

    ConsumerWrapper cw(*this);

    SubmitterPlugin *sp = getLoader().loadByInterfaceName(et.ComputingEndpoint->InterfaceName, uc);

    if (sp == NULL) {
      for (std::list<JobDescription>::const_iterator it = descs.begin(); it != descs.end(); ++it) {
        notsubmitted.push_back(&*it);
      }
      return SubmissionStatus::SUBMITTER_PLUGIN_NOT_LOADED;
    }

    return sp->Submit(descs, et, cw, notsubmitted);
  }
