subscription(uint8_t buf[], uint16_t message_id,
                    const char *event_name, const char *device_id)
{
  uint8_t *p = subscription_prelude(buf, message_id, event_name);

  if (NULL != device_id)
  {
    size_t len = strnlen(device_id, 63);

    *p++ = 0xff;
    memcpy(p, device_id, len);
    p += len;
  }

  return p - buf;
}
