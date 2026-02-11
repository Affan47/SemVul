parse_packet(struct cvm_packet* p)
{
  if (p->data[0] != 0)
    return p->data[0];
  if (p->length < 3
      || p->data[p->length-1] != 0
      || p->data[p->length-2] != 0)
    return CVME_BAD_MODDATA;
  if (cvm_client_fact_str(CVM_FACT_USERNAME, &cvm_fact_username) ||
      cvm_client_fact_uint(CVM_FACT_USERID, &cvm_fact_userid) ||
      cvm_client_fact_uint(CVM_FACT_GROUPID, &cvm_fact_groupid) ||
      cvm_client_fact_str(CVM_FACT_DIRECTORY, &cvm_fact_directory))
    return CVME_BAD_MODDATA;
  cvm_client_fact_str(CVM_FACT_SHELL, &cvm_fact_shell);
  cvm_client_fact_str(CVM_FACT_REALNAME, &cvm_fact_realname);
  cvm_client_fact_str(CVM_FACT_GROUPNAME, &cvm_fact_groupname);
  cvm_client_fact_str(CVM_FACT_SYS_USERNAME, &cvm_fact_sys_username);
  cvm_client_fact_str(CVM_FACT_SYS_DIRECTORY, &cvm_fact_sys_directory);
  cvm_client_fact_str(CVM_FACT_DOMAIN, &cvm_fact_domain);
  cvm_client_fact_str(CVM_FACT_MAILBOX, &cvm_fact_mailbox);
  return 0;
}
