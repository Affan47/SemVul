transmit_packet(NTP_Mode my_mode,
                int my_poll,
                int version,
                int do_auth,
                unsigned long key_id,
                NTP_int64 *orig_ts,
                struct timeval *local_rx,
                struct timeval *local_tx,


                NTP_int64 *local_ntp_tx,


                NTP_Remote_Address *where_to
                )
{
  NTP_Packet message;
  int leap;
  struct timeval local_transmit;


  int are_we_synchronised, our_stratum;
  NTP_Leap leap_status;
  uint32_t our_ref_id, ts_fuzz;
  struct timeval our_ref_time;
  double our_root_delay, our_root_dispersion;


  if (version > NTP_VERSION) {
    version = NTP_VERSION;
  }


  SCH_GetLastEventTime(&local_transmit, NULL, NULL);

  REF_GetReferenceParams(&local_transmit,
                         &are_we_synchronised, &leap_status,
                         &our_stratum,
                         &our_ref_id, &our_ref_time,
                         &our_root_delay, &our_root_dispersion);

  if (are_we_synchronised) {
    leap = (int) leap_status;
  } else {
    leap = LEAP_Unsynchronised;
  }


  message.lvm = ((leap << 6) &0xc0) | ((version << 3) & 0x38) | (my_mode & 0x07);
  if (our_stratum <= NTP_MAX_STRATUM) {
    message.stratum = our_stratum;
  } else {

    message.stratum = NTP_INVALID_STRATUM;
  }

  message.poll = my_poll;
  message.precision = LCL_GetSysPrecisionAsLog();


  message.root_delay = UTI_DoubleToInt32(our_root_delay);
  message.root_dispersion = UTI_DoubleToInt32(our_root_dispersion);

  message.reference_id = htonl((NTP_int32) our_ref_id);


  UTI_TimevalToInt64(&our_ref_time, &message.reference_ts, 0);


  message.originate_ts = *orig_ts;


  UTI_TimevalToInt64(local_rx, &message.receive_ts, 0);


  ts_fuzz = UTI_GetNTPTsFuzz(message.precision);


  LCL_ReadCookedTime(&local_transmit, NULL);


  if (do_auth) {
    int auth_len;


    local_transmit.tv_usec += KEY_GetAuthDelay(key_id);
    UTI_NormaliseTimeval(&local_transmit);
    UTI_TimevalToInt64(&local_transmit, &message.transmit_ts, ts_fuzz);

    auth_len = KEY_GenerateAuth(key_id, (unsigned char *) &message,
        offsetof(NTP_Packet, auth_keyid),
        (unsigned char *)&message.auth_data, sizeof (message.auth_data));
    if (auth_len > 0) {
      message.auth_keyid = htonl(key_id);
      NIO_SendAuthenticatedPacket(&message, where_to,
          sizeof (message.auth_keyid) + auth_len);
    }
  } else {
    UTI_TimevalToInt64(&local_transmit, &message.transmit_ts, ts_fuzz);
    NIO_SendNormalPacket(&message, where_to);
  }

  if (local_tx) {
    *local_tx = local_transmit;
  }

  if (local_ntp_tx) {
    *local_ntp_tx = message.transmit_ts;
  }

}
