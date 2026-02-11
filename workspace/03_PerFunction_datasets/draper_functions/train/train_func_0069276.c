xsh_pfits_set_qc_ron_master (cpl_propertylist * plist, double value)
{
  check_msg (cpl_propertylist_update_double (plist,XSH_QC_MASTER_RON,value),
             "Error writing keyword '%s'", XSH_QC_MASTER_RON);
  cpl_propertylist_set_comment(plist,XSH_QC_MASTER_RON,XSH_QC_MASTER_RON_C);

cleanup:
  return;
}
