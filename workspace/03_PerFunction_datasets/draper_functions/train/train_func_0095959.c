ssl_wrapper_init(const char *local_addr, const char *target_addr,
                       const char **err_msg) {
  struct ns_mgr *mgr = (struct ns_mgr *) calloc(1, sizeof(mgr[0]));
  *err_msg = NULL;

  if (mgr == NULL) {
    *err_msg = "malloc failed";
  } else {
    ns_mgr_init(mgr, (void *) target_addr);
    if (ns_bind(mgr, local_addr, ev_handler, NULL) == NULL) {
      *err_msg = "ns_bind() failed: bad listening_port";
      ns_mgr_free(mgr);
      free(mgr);
      mgr = NULL;
    }
  }

  return mgr;
}
