leveldb_options_set_info_log(leveldb_options_t* opt, leveldb_logger_t* l) {
  opt->rep.info_log = (l ? l->rep : NULL);
}
