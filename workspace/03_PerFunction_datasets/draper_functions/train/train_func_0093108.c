cvm_module_lookup(void)
{
  static str path;
  int r;

  switch (qmail_lookup_cvm(&user, &domain, &username, &ext)) {
  case -1:
    return CVME_IO;
  case 0:
    break;
  case 1:
    cvm_module_fact_uint(CVM_FACT_OUTOFSCOPE, 1);
    return CVME_PERMFAIL;
  default:
    cvm_module_fact_uint(CVM_FACT_OUTOFSCOPE, 0);
    return CVME_PERMFAIL;
  }

  if (check_perms) {
    setegid(user.gid);
    seteuid(user.uid);
  }
  r = qmail_dotfile_exists(&user, ext.s, &path);
  if (check_perms) {
    seteuid(saved_uid);
    setegid(saved_gid);
  }
  switch (r) {
  case -1:
    if (errno == EACCES && check_perms == CVME_PERMFAIL) {
      cvm_module_fact_uint(CVM_FACT_OUTOFSCOPE, 0);
      return CVME_PERMFAIL;
    }
    return CVME_IO;
  case 0:
    cvm_module_fact_uint(CVM_FACT_OUTOFSCOPE, 0);
    return CVME_PERMFAIL;
  }

  if (programs.len > 0) {
    switch (lookup_programs(&path)) {
    case -1:
      return CVME_IO;
    case 0:
      break;
    default:
      cvm_module_fact_uint(CVM_FACT_OUTOFSCOPE, 1);
      return CVME_PERMFAIL;
    }
  }

  return 0;
}
