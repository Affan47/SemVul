do_flush_all(kt::ThreadedServer* serv, kt::ThreadedServer::Session* sess,
                      const std::vector<std::string>& tokens, kt::TimedDB* db) {
      uint32_t thid = sess->thread_id();
      if (tokens.size() < 1) return sess->printf("CLIENT_ERROR invalid parameters\r\n");
      bool norep = false;
      for (size_t i = 1; i < tokens.size(); i++) {
        if (tokens[i] == "noreply") norep = true;
      }
      bool err = false;
      opcounts_[thid][CNTFLUSH]++;
      std::map<std::string, std::string> status;
      if (db->clear()) {
        if (!norep && !sess->printf("OK\r\n")) err = true;
      } else {
        const kc::BasicDB::Error& e = db->error();
        log_db_error(serv, e);
        if (!norep && !sess->printf("SERVER_ERROR DB::clear failed\r\n")) err = true;
      }
      return !err;
    }
