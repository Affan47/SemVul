checkmsgti(llnodeT* target, char* tab)
{
  if (strcmp(tab, "LOG_T_ALL") == 0) {
    target->msgtype |= LOG_T_ALL;
  }
  else if (strcmp(tab, "LOG_T_USER") == 0) {
    target->msgtype |= LOG_T_USER;
  }
  else if (strcmp(tab, "LOG_T_CLIENT") == 0) {
    target->msgtype |= LOG_T_CLIENT;
  }
  else if (strcmp(tab, "LOG_T_INIT") == 0) {
    target->msgtype |= LOG_T_INIT;
  }
  else if (strcmp(tab, "LOG_T_MANAGE") == 0) {
    target->msgtype |= LOG_T_MANAGE;
  }
  else if (strcmp(tab, "LOG_T_MAIN") == 0) {
    target->msgtype |= LOG_T_MAIN;
  }
  else if (strcmp(tab, "LOG_I_ALL") == 0) {
    target->importance |= LOG_I_ALL;
  }
  else if (strcmp(tab, "LOG_I_CRIT") == 0) {
    target->importance |= LOG_I_CRIT;
  }
  else if (strcmp(tab, "LOG_I_DEBUG") == 0) {
    target->importance |= LOG_I_DEBUG;
  }
  else if (strcmp(tab, "LOG_I_INFO") == 0) {
    target->importance |= LOG_I_INFO;
  }
  else if (strcmp(tab, "LOG_I_NOTICE") == 0) {
    target->importance |= LOG_I_NOTICE;
  }
  else if (strcmp(tab, "LOG_I_WARNING") == 0) {
    target->importance |= LOG_I_WARNING;
  }
  else if (strcmp(tab, "LOG_I_ERR") == 0) {
    target->importance |= LOG_I_ERR;
  }
  else {
    return 1;
  }
  return 0;
}
