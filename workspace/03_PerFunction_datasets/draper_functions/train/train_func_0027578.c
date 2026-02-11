TryParseLocked(const CommandLineFlag* flag, FlagValue* flag_value,
                    const char* value, string* msg) {

  FlagValue* tentative_value = flag_value->New();
  if (!tentative_value->ParseFrom(value)) {
    if (msg) {
      StringAppendF(msg,
                    "%sillegal value '%s' specified for %s flag '%s'\n",
                    kError, value,
                    flag->type_name(), flag->name());
    }
    delete tentative_value;
    return false;
  } else if (!flag->Validate(*tentative_value)) {
    if (msg) {
      StringAppendF(msg,
          "%sfailed validation of new value '%s' for flag '%s'\n",
          kError, tentative_value->ToString().c_str(),
          flag->name());
    }
    delete tentative_value;
    return false;
  } else {
    flag_value->CopyFrom(*tentative_value);
    if (msg) {
      StringAppendF(msg, "%s set to %s\n",
                    flag->name(), flag_value->ToString().c_str());
    }
    delete tentative_value;
    return true;
  }
}
