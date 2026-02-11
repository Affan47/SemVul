ssh_client_ecdh_init(ssh_session session){
  EC_KEY *key;
  const EC_GROUP *group;
  const EC_POINT *pubkey;
  ssh_string client_pubkey;
  int len;
  int rc;
  bignum_CTX ctx = BN_CTX_new();

  rc = buffer_add_u8(session->out_buffer, SSH2_MSG_KEX_ECDH_INIT);
  if (rc < 0) {
      BN_CTX_free(ctx);
      return SSH_ERROR;
  }

  key = EC_KEY_new_by_curve_name(NISTP256);
  if (key == NULL) {
      BN_CTX_free(ctx);
      return SSH_ERROR;
  }
  group = EC_KEY_get0_group(key);

  EC_KEY_generate_key(key);

  pubkey=EC_KEY_get0_public_key(key);
  len = EC_POINT_point2oct(group,pubkey,POINT_CONVERSION_UNCOMPRESSED,
      NULL,0,ctx);

  client_pubkey = ssh_string_new(len);
  if (client_pubkey == NULL) {
      BN_CTX_free(ctx);
      EC_KEY_free(key);
      return SSH_ERROR;
  }

  EC_POINT_point2oct(group,pubkey,POINT_CONVERSION_UNCOMPRESSED,
      ssh_string_data(client_pubkey),len,ctx);
  BN_CTX_free(ctx);

  rc = buffer_add_ssh_string(session->out_buffer,client_pubkey);
  if (rc < 0) {
      EC_KEY_free(key);
      ssh_string_free(client_pubkey);
      return SSH_ERROR;
  }

  session->next_crypto->ecdh_privkey = key;
  session->next_crypto->ecdh_client_pubkey = client_pubkey;

  rc = packet_send(session);

  return rc;
}
