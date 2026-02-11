_cleanFilesAndReturnFalse(const std::string& hard_link_file,
                                            bool& locked) {
    if (!FileDelete(hard_link_file)) logger.msg(ERROR, "Failed to clean up file %s: %s", hard_link_file, StrError(errno));
    locked = true;
    return false;
  }

}
