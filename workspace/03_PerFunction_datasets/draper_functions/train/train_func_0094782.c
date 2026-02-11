insert(const ExecutionTarget& et) {
    std::list<ExecutionTarget>::iterator insertPosition = targets.first.begin();
    for (; insertPosition != targets.first.end(); ++insertPosition) {
      if ((*b)(et, *insertPosition)) {
        break;
      }
    }
    targets.first.insert(insertPosition, et);
  }
