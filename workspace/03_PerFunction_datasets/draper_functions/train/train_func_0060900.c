SetEnv(const std::string& var, const std::string& value, bool overwrite) {
    SharedMutexExclusive env_lock(env_read_lock());
#ifndef TRICKED_ENVIRONMENT
#ifdef HAVE_GLIBMM_SETENV
    return Glib::setenv(var, value, overwrite);
#else
#ifdef HAVE_SETENV
    return (setenv(var.c_str(), value.c_str(), overwrite) == 0);
#else
    return (putenv(strdup((var + "=" + value).c_str())) == 0);
#endif
#endif
#else
    return TrickEnvRecord::Set(var, value, overwrite);
#endif
  }
