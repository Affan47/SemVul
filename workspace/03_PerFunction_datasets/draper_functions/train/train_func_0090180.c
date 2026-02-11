NCR_TakeSourceOnline(NCR_Instance inst)
{
  switch (inst->opmode) {
    case MD_ONLINE:

      break;
    case MD_OFFLINE:
      if (!inst->timer_running) {

        LOG(LOGS_INFO, LOGF_NtpCore, "Source %s online", UTI_IPToString(&inst->remote_addr.ip_addr));
        inst->tx_count = 0;
        inst->local_poll = inst->minpoll;
        inst->poll_score = 0.5;
        inst->opmode = MD_ONLINE;
        start_initial_timeout(inst);
      }
      break;
    case MD_BURST_WAS_ONLINE:

      break;
    case MD_BURST_WAS_OFFLINE:
      inst->opmode = MD_BURST_WAS_ONLINE;
      LOG(LOGS_INFO, LOGF_NtpCore, "Source %s online", UTI_IPToString(&inst->remote_addr.ip_addr));
      break;
  }
}
