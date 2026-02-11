printsummary(const std::list<Arc::JobDescription>& originalDescriptions, const std::list<const Arc::JobDescription*>& notsubmitted) const {
    if (originalDescriptions.size() > 1) {
      std::cout << std::endl << Arc::IString("Job submission summary:") << std::endl;
      std::cout << "-----------------------" << std::endl;
      std::cout << Arc::IString("%d of %d jobs were submitted", submittedJobs.size(), submittedJobs.size()+notsubmitted.size()) << std::endl;
      if (!notsubmitted.empty()) {
        std::cout << Arc::IString("The following %d were not submitted", notsubmitted.size()) << std::endl;
        for (std::list<const Arc::JobDescription*>::const_iterator it = notsubmitted.begin();
             it != notsubmitted.end(); ++it) {
          int jobnr = 1;
          for (std::list<Arc::JobDescription>::const_iterator itOrig = originalDescriptions.begin();
               itOrig != originalDescriptions.end(); ++itOrig, ++jobnr) {
            if (&(*itOrig) == *it) {
              std::cout << Arc::IString("Job nr.") << " " << jobnr;
              if (!(*it)->Identification.JobName.empty()) {
                std::cout << ": " << (*it)->Identification.JobName;
              }
              std::cout << std::endl;
              break;
            }
          }
        }
      }
    }
  }
