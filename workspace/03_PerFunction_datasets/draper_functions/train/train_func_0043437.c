note_crypto_pk_op(pk_op_t operation)
{
  switch (operation)
    {
    case SIGN_DIR:
      pk_op_counts.n_signed_dir_objs++;
      break;
    case SIGN_RTR:
      pk_op_counts.n_signed_routerdescs++;
      break;
    case VERIFY_DIR:
      pk_op_counts.n_verified_dir_objs++;
      break;
    case VERIFY_RTR:
      pk_op_counts.n_verified_routerdescs++;
      break;
    case ENC_ONIONSKIN:
      pk_op_counts.n_onionskins_encrypted++;
      break;
    case DEC_ONIONSKIN:
      pk_op_counts.n_onionskins_decrypted++;
      break;
    case TLS_HANDSHAKE_C:
      pk_op_counts.n_tls_client_handshakes++;
      break;
    case TLS_HANDSHAKE_S:
      pk_op_counts.n_tls_server_handshakes++;
      break;
    case REND_CLIENT:
      pk_op_counts.n_rend_client_ops++;
      break;
    case REND_MID:
      pk_op_counts.n_rend_mid_ops++;
      break;
    case REND_SERVER:
      pk_op_counts.n_rend_server_ops++;
      break;
    default:
      log_warn(LD_BUG, "Unknown pk operation %d", operation);
  }
}
