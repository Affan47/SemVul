_ds_encode_block (ds_message_part_t block, int encoding)
{


  if (block->encoding == encoding)
    return EINVAL;


  if (block->encoding == EN_BASE64 || block->encoding == EN_QUOTED_PRINTABLE)
    return EFAILURE;

  if (encoding == EN_BASE64) {
    char *encoded = _ds_encode_base64 (block->body->data);
    buffer_destroy (block->body);
    block->body = buffer_create (encoded);
    free (encoded);
    block->encoding = EN_BASE64;
  }
  else if (encoding == EN_QUOTED_PRINTABLE) {


    return 0;
  }

  LOGDEBUG("unsupported encoding: %d", encoding);
  return 0;
}
