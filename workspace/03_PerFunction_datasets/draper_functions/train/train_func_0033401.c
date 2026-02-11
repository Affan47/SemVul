SelectByID(const std::list<std::string>& ids) {
    processed.clear();
    notprocessed.clear();

    if (ids.empty()) {
      return;
    }

    for (JobSelectionMap::iterator it = jcJobMap.begin();
         it != jcJobMap.end(); ++it) {
      for (std::list<Job*>::iterator itJ = it->second.first.begin();
           itJ != it->second.first.end();) {
        if (std::find(ids.begin(), ids.end(), (*itJ)->JobID) == ids.end()) {
          notprocessed.push_back((*itJ)->JobID);
          it->second.second.push_back(*itJ);
          itJ = it->second.first.erase(itJ);
        }
        else {
          processed.push_back((*itJ)->JobID);
          ++itJ;
        }
      }
    }
  }
