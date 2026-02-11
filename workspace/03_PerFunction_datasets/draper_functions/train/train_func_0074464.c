bootstrap_status_to_string(bootstrap_status_t s, const char **tag,
                           const char **summary)
{
  switch (s) {
    case BOOTSTRAP_STATUS_UNDEF:
      *tag = "undef";
      *summary = "Undefined";
      break;
    case BOOTSTRAP_STATUS_STARTING:
      *tag = "starting";
      *summary = "Starting";
      break;
    case BOOTSTRAP_STATUS_CONN_DIR:
      *tag = "conn_dir";
      *summary = "Connecting to directory server";
      break;
    case BOOTSTRAP_STATUS_HANDSHAKE:
      *tag = "status_handshake";
      *summary = "Finishing handshake";
      break;
    case BOOTSTRAP_STATUS_HANDSHAKE_DIR:
      *tag = "handshake_dir";
      *summary = "Finishing handshake with directory server";
      break;
    case BOOTSTRAP_STATUS_ONEHOP_CREATE:
      *tag = "onehop_create";
      *summary = "Establishing an encrypted directory connection";
      break;
    case BOOTSTRAP_STATUS_REQUESTING_STATUS:
      *tag = "requesting_status";
      *summary = "Asking for networkstatus consensus";
      break;
    case BOOTSTRAP_STATUS_LOADING_STATUS:
      *tag = "loading_status";
      *summary = "Loading networkstatus consensus";
      break;
    case BOOTSTRAP_STATUS_LOADING_KEYS:
      *tag = "loading_keys";
      *summary = "Loading authority key certs";
      break;
    case BOOTSTRAP_STATUS_REQUESTING_DESCRIPTORS:
      *tag = "requesting_descriptors";
      *summary = "Asking for relay descriptors";
      break;
    case BOOTSTRAP_STATUS_LOADING_DESCRIPTORS:
      *tag = "loading_descriptors";
      *summary = "Loading relay descriptors";
      break;
    case BOOTSTRAP_STATUS_CONN_OR:
      *tag = "conn_or";
      *summary = "Connecting to the Tor network";
      break;
    case BOOTSTRAP_STATUS_HANDSHAKE_OR:
      *tag = "handshake_or";
      *summary = "Finishing handshake with first hop";
      break;
    case BOOTSTRAP_STATUS_CIRCUIT_CREATE:
      *tag = "circuit_create";
      *summary = "Establishing a Tor circuit";
      break;
    case BOOTSTRAP_STATUS_DONE:
      *tag = "done";
      *summary = "Done";
      break;
    default:

      *tag = *summary = "unknown";
      return -1;
  }
  return 0;
}
