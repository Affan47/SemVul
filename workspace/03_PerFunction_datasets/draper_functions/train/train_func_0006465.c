Connect(const URL& url,
                           const UserConfig& uc) {

    int timeout = uc.Timeout();
    bool timedin;
    GlobusResult result;

    result = globus_ftp_control_handle_init(&control_handle);
    if (!result) {
      logger.msg(VERBOSE, "Connect: Failed to init handle: %s", result.str());
      return false;
    }

    result = globus_ftp_control_ipv6_allow(&control_handle, GLOBUS_TRUE);
    if (!result) {
      logger.msg(VERBOSE, "Failed to enable IPv6: %s", result.str());
    }

    cb->ctrl = false;
    connected = true;
    result = globus_ftp_control_connect(&control_handle,
                                        const_cast<char*>(url.Host().c_str()),
                                        url.Port(), &ConnectCallback,
                                        cb);
    if (!result) {
      logger.msg(VERBOSE, "Connect: Failed to connect: %s", result.str());
      connected = false;
      return false;
    }
    while (!cb->ctrl) {
      timedin = cb->cond.wait(timeout * 1000);
      if (!timedin) {
        logger.msg(VERBOSE, "Connect: Connecting timed out after %d ms",
                   timeout * 1000);
        Disconnect(timeout);
        return false;
      }
    }
    if (!cb->responseok) {
      logger.msg(VERBOSE, "Connect: Failed to connect: %s", cb->Response());
      Disconnect(timeout);
      return false;
    }

    GSSCredential handle(uc);

    globus_ftp_control_auth_info_t auth;
    result = globus_ftp_control_auth_info_init(&auth, handle, GLOBUS_TRUE,
                                               const_cast<char*>("ftp"),
                                               const_cast<char*>("user@"),
                                               GLOBUS_NULL, GLOBUS_NULL);
    if (!result) {
      logger.msg(VERBOSE, "Connect: Failed to init auth info handle: %s",
                 result.str());
      Disconnect(timeout);
      return false;
    }

    cb->ctrl = false;
    result = globus_ftp_control_authenticate(&control_handle, &auth,
                                             GLOBUS_TRUE,
                                             &ControlCallback, cb);
    if (!result) {
      logger.msg(VERBOSE, "Connect: Failed authentication: %s", result.str());
      Disconnect(timeout);
      return false;
    }
    while (!cb->ctrl) {
      timedin = cb->cond.wait(timeout * 1000);
      if (!timedin) {
        logger.msg(VERBOSE, "Connect: Authentication timed out after %d ms",
                   timeout * 1000);
        Disconnect(timeout);
        return false;
      }
    }
    if (!cb->responseok) {
      logger.msg(VERBOSE, "Connect: Failed authentication: %s", cb->Response());
      Disconnect(timeout);
      return false;
    }

    return true;

  }
