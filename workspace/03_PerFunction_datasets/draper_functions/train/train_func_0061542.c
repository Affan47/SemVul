force_abort(void) {
  globus_mutex_lock(&abort_lock);
  if(transfer_abort || (!transfer_mode)) {

    globus_mutex_unlock(&abort_lock);
    return;
  };
  logger.msg(Arc::INFO, "Abort request caused by error in transfer function");

  if(froot.error.length()) {
    send_response("426 "+froot.error+"\r\n");
  } else {
    send_response("426 Transfer terminated.\r\n");
  };
  globus_mutex_unlock(&data_lock);
  make_abort(true,false);
  globus_mutex_lock(&data_lock);
  return;
}
