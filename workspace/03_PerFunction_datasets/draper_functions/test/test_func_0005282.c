match_submission_interface(const ExecutionTarget& target, const std::list<std::string>& requestedSubmissionInterfaces) {
    if (requestedSubmissionInterfaces.empty()) return true;
    for (std::list<std::string>::const_iterator iname = requestedSubmissionInterfaces.begin();
                  iname != requestedSubmissionInterfaces.end(); ++iname) {
      if (*iname == target.ComputingEndpoint->InterfaceName) return true;
    }
    return false;
  }
