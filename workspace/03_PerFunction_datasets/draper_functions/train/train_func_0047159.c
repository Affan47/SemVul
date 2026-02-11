key_file_error_report(file_test_status fts, bool require, const std::string& path, Logger& logger) {
    if(fts == file_test_success) {
    } else if(fts == file_test_wrong_ownership) {
      logger.msg(require?ERROR:VERBOSE, "Wrong ownership of key file: %s", path);
    } else if(fts == file_test_wrong_permissions) {
      logger.msg(require?ERROR:VERBOSE, "Wrong permissions of key file: %s", path);
    } else {
      logger.msg(require?ERROR:VERBOSE, "Can not access key file: %s", path);
    }
  }
