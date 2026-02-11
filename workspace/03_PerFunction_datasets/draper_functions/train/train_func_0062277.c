getSubmittedVia() const {
    for (XMLNode n = jobInfo["ActivityInfoDocument"]["OtherInfo"]; (bool)n; ++n) {
      const std::string submittedvia = "SubmittedVia=";
      if (((std::string)n).substr(0, submittedvia.length()) == submittedvia) {
        return ((std::string)n).substr(submittedvia.length());
      }
    }

    return "";
  }
