registerJobSubmission() {
    if (endOfList()) {
      return;
    }

    if (b == NULL || !b->isValid()) {
      logger.msg(DEBUG, "Unable to register job submission. Can't get JobDescription object from Broker, Broker is invalid.");
      return;
    }

    current->RegisterJobSubmission(b->getJobDescription());

    targets.second.push_back(*current);
    targets.first.erase(current);

    if (b->match(targets.second.back())) {
      insert(targets.second.back());
      targets.second.pop_back();
    }

    reset();
  }
}
