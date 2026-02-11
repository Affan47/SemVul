Clean() {
    notprocessed.clear();
    processed.clear();
    bool ok = true;

    for (JobSelectionMap::iterator it = jcJobMap.begin();
         it != jcJobMap.end(); ++it) {
      for (std::list<Job*>::iterator itJ = it->second.first.begin();
           itJ != it->second.first.end();) {
        if (!(*itJ)->State || !(*itJ)->State.IsFinished()) {
          notprocessed.push_back((*itJ)->JobID);
          it->second.second.push_back(*itJ);
          itJ = it->second.first.erase(itJ);
          continue;
        }

        if (!it->first->CleanJobs(std::list<Job*>(1, *itJ), processed, notprocessed)) {
          ok = false;
          it->second.second.push_back(*itJ);
          itJ = it->second.first.erase(itJ);
        }
        else {
          ++itJ;
        }
      }
    }

    return ok;
  }
