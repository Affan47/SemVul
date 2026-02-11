info_NeedMoreFiles(ProgressReporter& reporter, const string& tmpName) {
    string info = subst(_(
          "Copied input files to temporary file `%1' - "
          "repeat command and supply more files to continue"), tmpName);
    reporter.info(info);
    return 1;
  }
