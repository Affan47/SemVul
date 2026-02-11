lam_send_selected_ssi_modules(void)
{
  lam_ssi_module_t *module;
  lam_ssi_rpi_t rpi;
  lam_ssi_crmpi_t crmpi;
  struct nmsg nhead;
  struct mpi_app_extra_info maei;

  if (0 == getenv("LAMRANK"))
    return LAMERROR;


  LAM_ZERO_ME(maei);
  LAM_ZERO_ME(nhead);
  nhead.nh_node = _kio.ki_jobid.jid_node;
  nhead.nh_event = (-_kio.ki_jobid.jid_pid) & 0xBFFFFFFF;
  nhead.nh_type = 2;
  nhead.nh_flags = DINT4DATA;


  nhead.nh_data[0] = lam_myproc->p_gps.gps_grank;

  nhead.nh_length = sizeof(maei);
  nhead.nh_msg = (char *) &maei;


  module = (lam_ssi_module_t *) al_top(lam_ssi_rpi_base_available);
  rpi = *((lam_ssi_rpi_t *) module->lsm_module);
  memcpy(maei.maei_rpi.masi_name,
         rpi.lsr_meta_info.ssi_module_name,
         sizeof(maei.maei_rpi.masi_name));
  maei.maei_rpi.masi_major_ver =
    ltot(rpi.lsr_meta_info.ssi_module_major_version);
  maei.maei_rpi.masi_minor_ver =
    ltot(rpi.lsr_meta_info.ssi_module_minor_version);
  maei.maei_rpi.masi_release_ver =
    ltot(rpi.lsr_meta_info.ssi_module_release_version);


  if (mpi_nparent == 0) {
    if (lam_ssi_crmpi_base_available != NULL) {
      module = (lam_ssi_module_t *) al_top(lam_ssi_crmpi_base_available);
    }
  } else {
    module = NULL;
  }

  if ((NULL == lam_ssi_crmpi_base_available) ||
      (NULL == module)) {
    strcpy(maei.maei_crmpi.masi_name, "none");
    maei.maei_crmpi.masi_major_ver = -1;
    maei.maei_crmpi.masi_minor_ver = -1;
    maei.maei_crmpi.masi_release_ver = -1;
  } else {
    crmpi = *((lam_ssi_crmpi_t *) module->lsm_module);
    memcpy(maei.maei_crmpi.masi_name,
           crmpi.lscrm_meta_info.ssi_module_name,
           sizeof(maei.maei_crmpi.masi_name));
    maei.maei_crmpi.masi_major_ver =
      ltot(crmpi.lscrm_meta_info.ssi_module_major_version);
    maei.maei_crmpi.masi_minor_ver =
      ltot(crmpi.lscrm_meta_info.ssi_module_minor_version);
    maei.maei_crmpi.masi_release_ver =
      ltot(crmpi.lscrm_meta_info.ssi_module_release_version);
  }

  if (nsend(&nhead))
    return LAMERROR;

  return 0;
}
