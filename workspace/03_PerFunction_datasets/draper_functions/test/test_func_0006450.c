lam_ssi_boot_globus_verify_nodes(struct lamnode *nodes, int nnodes)
{
  int i;


  if (lam_ssi_boot_verbose >= 1) {
    lam_debug(lam_ssi_boot_did, "globus: resolved hosts:");
    for (i = 0; i < nnodes; ++i) {
      if (nodes[i].lnd_nodeid != NOTNODEID)
        lam_debug(lam_ssi_boot_did, "globus:   n%d %s --> %s%s",
                  i, nodes[i].lnd_hname, inet_ntoa(nodes[i].lnd_addr.sin_addr),
                  (i == origin) ? " (origin)" : "");
      else
        lam_debug(lam_ssi_boot_did, "globus:   n%d invalid node", i);
    }
  }


  if (nnodes > 1 && !ao_taken(lam_ssi_boot_optd, "l")) {
    if (inet_netof(nodes[origin].lnd_addr.sin_addr) == 127) {
      show_help("boot-ssi", "resolve-localhost",
		"The boot SSI globus module", nodes[origin].lnd_hname,
		inet_ntoa(nodes[origin].lnd_addr.sin_addr));
      return LAMERROR;
    }
  }

  return 0;

}
