circuit_purpose_to_controller_hs_state_string(uint8_t purpose)
{
  switch (purpose)
    {
    default:
      log_fn(LOG_WARN, LD_BUG,
             "Unrecognized circuit purpose: %d",
             (int)purpose);
      tor_fragile_assert();


    case CIRCUIT_PURPOSE_OR:
    case CIRCUIT_PURPOSE_C_GENERAL:
    case CIRCUIT_PURPOSE_C_MEASURE_TIMEOUT:
    case CIRCUIT_PURPOSE_TESTING:
    case CIRCUIT_PURPOSE_CONTROLLER:
      return NULL;

    case CIRCUIT_PURPOSE_INTRO_POINT:
      return "OR_HSSI_ESTABLISHED";
    case CIRCUIT_PURPOSE_REND_POINT_WAITING:
      return "OR_HSCR_ESTABLISHED";
    case CIRCUIT_PURPOSE_REND_ESTABLISHED:
      return "OR_HS_R_JOINED";

    case CIRCUIT_PURPOSE_C_INTRODUCING:
      return "HSCI_CONNECTING";
    case CIRCUIT_PURPOSE_C_INTRODUCE_ACK_WAIT:
      return "HSCI_INTRO_SENT";
    case CIRCUIT_PURPOSE_C_INTRODUCE_ACKED:
      return "HSCI_DONE";

    case CIRCUIT_PURPOSE_C_ESTABLISH_REND:
      return "HSCR_CONNECTING";
    case CIRCUIT_PURPOSE_C_REND_READY:
      return "HSCR_ESTABLISHED_IDLE";
    case CIRCUIT_PURPOSE_C_REND_READY_INTRO_ACKED:
      return "HSCR_ESTABLISHED_WAITING";
    case CIRCUIT_PURPOSE_C_REND_JOINED:
      return "HSCR_JOINED";

    case CIRCUIT_PURPOSE_S_ESTABLISH_INTRO:
      return "HSSI_CONNECTING";
    case CIRCUIT_PURPOSE_S_INTRO:
      return "HSSI_ESTABLISHED";

    case CIRCUIT_PURPOSE_S_CONNECT_REND:
      return "HSSR_CONNECTING";
    case CIRCUIT_PURPOSE_S_REND_JOINED:
      return "HSSR_JOINED";
    }
}
