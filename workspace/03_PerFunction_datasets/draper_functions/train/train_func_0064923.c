onFailure(const std::string &error, bool &failed) throw ()
    {
        SE_LOG_DEBUG(NULL, "failure, quitting now: %s",  error.c_str());
        failed = true;
    }
