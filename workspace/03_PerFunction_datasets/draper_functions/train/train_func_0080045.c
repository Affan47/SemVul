lam_ssi_boot_base_send_lamd_info_args(OPT *aod, unsigned char agent_haddr[4],
                                      int agent_port, int node_id,
                                      int dli_port, int num_cpus)
{
  int agent_fd;


  if (agent_haddr[0] == 0 && agent_haddr[1] == 0 &&
      agent_haddr[2] == 0 && agent_haddr[3] == 0) {
    if (lam_ssi_boot_verbose >= 5)
      lam_debug(lam_ssi_boot_did,
                "send_lamd: getting agent haddr from command line");
    if (ao_taken(aod, "H"))
      gethaddr(ao_param(aod, "H", 0, 0), agent_haddr);
    else {
      show_help("ssi-boot", "base-startup-proto-missing-args", NULL);
      errno = EUSAGE;
      return 1;
    }
  }

  if (agent_port == -1) {
    if (lam_ssi_boot_verbose >= 5)
      lam_debug(lam_ssi_boot_did,
                "send_lamd: getting agent port from command line");
    if (ao_taken(aod, "P")) {
      ao_intparam(aod, "P", 0, 0, &agent_port);
    } else {
      show_help("ssi-boot", "base-startup-proto-missing-args", NULL);
      errno = EUSAGE;
      return 1;
    }
  }

  if (node_id == -1) {
    node_id = lam_ssi_boot_base_get_nodeid(aod);
  }

  if (lam_ssi_boot_verbose >= 5)
    lam_debug(lam_ssi_boot_did,
              "send_lamd: connecting to %d.%d.%d.%d:%d, node id %d",
              agent_haddr[0], agent_haddr[1], agent_haddr[2], agent_haddr[3],
              agent_port, node_id);

  if (agent_haddr[0] == '\0' || agent_port == -1 || node_id == -1) {
    show_help("ssi-boot", "base-startup-proto-missing-args", NULL);
    reply2agent(errno,
		"ssi_boot_send_lamd_info: missing cmd line args");
  }


  boot_port = 0;
  boot_fd = sfh_sock_open_srv_inet_stm(&boot_port, -1);
  if (boot_fd < 0)
    reply2agent(errno,
		"ssi_boot_send_lamd_info: sfh_sock_open_srv_inet_stm failed");


  agent_fd = sfh_sock_open_clt_inet_stm(agent_haddr, agent_port);
  if (agent_fd < 0)
    lampanic("ssi_boot_send_lamd_info: sfh_sock_open_clt_inet_stm failed");


  if (lam_ssi_boot_verbose >= 5)
    lam_debug(lam_ssi_boot_did, "send_lamd: sending dli_port %d", dli_port);
  if (writecltcoord(agent_fd, node_id, (int4) boot_port, (int4) dli_port))
    lampanic("ssi_boot_send_lamd_info: writecltcoord failed");
  if (writesockint4(agent_fd, num_cpus) != 0)
    lampanic("ssi_boot_send_lamd_info: writesockint(num_cpus) failed");


  if (close(agent_fd))
    lampanic("ssi_boot_send_lamd_info: close(agent_fd) failed");

  return 0;
}
