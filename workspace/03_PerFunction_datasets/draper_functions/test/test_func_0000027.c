lam_ssi_crmpi_self_finalize(void)
{
  lam_ssi_crmpi_self_thread_status_t status =
    LAM_SSI_CRMPI_SELF_THREAD_STATUS_DONE;

   lam_ssi_crmpi_base_finalize_lock();


  if (write(crmpi_self_filedesc[1], &status, sizeof(status)) !=
      sizeof(status)) {
    show_help_file("lam-ssi-crmpi-self-helpfile", "cr-self-signal",
		   "write-fail", NULL);

    close(crmpi_self_filedesc[0]);
    close(crmpi_self_filedesc[1]);
    return LAMERROR;
  }


 if (lam_thread_join(crmpi_self_thread, NULL) == -1) {
    show_help_file("lam-ssi-crmpi-self-helpfile", "cr-self-init",
		   "thread-join-fail", NULL);
    return LAMERROR;
  }

  return 0;
}
