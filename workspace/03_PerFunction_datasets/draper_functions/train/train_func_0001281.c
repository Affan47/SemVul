transmit_timeout(void *arg)
{
  NCR_Instance inst = (NCR_Instance) arg;
  double timeout_delay;
  int do_auth;

  inst->timer_running = 0;

  switch (inst->opmode) {
    case MD_BURST_WAS_ONLINE:

      if (inst->burst_total_samples_to_go <= 1)
        inst->opmode = MD_ONLINE;
    case MD_BURST_WAS_OFFLINE:
      if (inst->burst_total_samples_to_go <= 0)
        take_offline(inst);
      break;
    default:
      break;
  }

  if (inst->opmode == MD_OFFLINE) {
    return;
  }

#ifdef TRACEON
  LOG(LOGS_INFO, LOGF_NtpCore, "Transmit timeout for [%s:%d]",
      UTI_IPToString(&inst->remote_addr.ip_addr), inst->remote_addr.port);
#endif


  if ((inst->presend_minpoll > 0) &&
      (inst->presend_minpoll <= inst->local_poll) &&
      !inst->presend_done) {


    NIO_SendEcho(&inst->remote_addr);

    inst->presend_done = 1;


    inst->timer_running = 1;
    inst->timeout_id = SCH_AddTimeoutInClass(WARM_UP_DELAY, SAMPLING_SEPARATION,
                                             SAMPLING_RANDOMNESS,
                                             SCH_NtpSamplingClass,
                                             transmit_timeout, (void *)inst);

    return;
  }

  inst->presend_done = 0;

  ++inst->tx_count;


  if (inst->tx_count >= 2) {


    adjust_poll(inst, SRC_IsSyncPeer(inst->source) ? 0.1 : 0.25);

    SRC_UpdateReachability(inst->source, 0);

    if (inst->auto_offline && inst->tx_count >= 3) {
      NCR_TakeSourceOffline(inst);
    }
  }

  if (inst->do_auth && KEY_KeyKnown(inst->auth_key_id)) {
    do_auth = 1;
  } else {
    do_auth = 0;
  }

  transmit_packet(inst->mode, inst->local_poll,
                  NTP_VERSION,
                  do_auth, inst->auth_key_id,
                  &inst->remote_orig,
                  &inst->local_rx, &inst->local_tx, &inst->local_ntp_tx,
                  &inst->remote_addr);

  switch (inst->opmode) {
    case MD_BURST_WAS_ONLINE:
    case MD_BURST_WAS_OFFLINE:
      --inst->burst_total_samples_to_go;
      break;
    default:
      break;
  }


  timeout_delay = get_transmit_delay(inst, 1, 0.0);
  inst->timer_running = 1;
  inst->timeout_id = SCH_AddTimeoutInClass(timeout_delay, SAMPLING_SEPARATION,
                                           SAMPLING_RANDOMNESS,
                                           SCH_NtpSamplingClass,
                                           transmit_timeout, (void *)inst);
}
