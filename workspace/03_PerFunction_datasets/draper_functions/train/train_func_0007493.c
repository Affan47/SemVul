process(Message& inmsg, Message& outmsg) {

    if (ctx == GSS_C_NO_CONTEXT) {
      MCC_Status status = InitContext();
      if (!status)
        return status;
    }

    if (!inmsg.Payload())
      return MCC_Status();

    PayloadRawInterface *inpayload =
      dynamic_cast<PayloadRawInterface*>(inmsg.Payload());

    if (!ProcessSecHandlers(inmsg, "outgoing")) {
      logger.msg(ERROR,
                 "Security check failed in GSI MCC for outgoing message");
      return MCC_Status();
    }

    PayloadRaw gsipayload;
    int size = 0;

    for (int n = 0; inpayload->Buffer(n); ++n) {

      gss_buffer_desc recv_tok = GSS_C_EMPTY_BUFFER;
      gss_buffer_desc send_tok = GSS_C_EMPTY_BUFFER;

      recv_tok.value = inpayload->Buffer(n);
      recv_tok.length = inpayload->BufferSize(n);

      logger.msg(VERBOSE, "Recieved token length: %i", recv_tok.length);

      OM_uint32 majstat, minstat;

      majstat = gss_wrap(&minstat,
                         ctx,
                         0,
                         GSS_C_QOP_DEFAULT,
                         &recv_tok,
                         NULL,
                         &send_tok);
      if (GSS_ERROR(majstat)) {
        logger.msg(ERROR, "GSS wrap failed: %i/%i%s", majstat, minstat, GSSCredential::ErrorStr(majstat, minstat));
        return MCC_Status();
      }

      logger.msg(INFO, "GSS wrap: %i/%i", majstat, minstat);

      logger.msg(VERBOSE, "Sent token length: %i", send_tok.length);

      gsipayload.Insert((const char*)send_tok.value, size, send_tok.length);
      size += send_tok.length;
    }

    Message nextinmsg = inmsg;
    nextinmsg.Payload(&gsipayload);
    Message nextoutmsg = outmsg;
    nextoutmsg.Payload(NULL);

    MCCInterface *next = MCC::Next();
    if (!next)
      return MCC_Status();
    MCC_Status ret = next->process(nextinmsg, nextoutmsg);


    if (!ProcessSecHandlers(outmsg, "incoming")) {
      logger.msg(ERROR,
                 "Security check failed in GSI MCC for incoming message");
      return MCC_Status();
    }

    PayloadStreamInterface *payload =
      dynamic_cast<PayloadStreamInterface*>(nextoutmsg.Payload());

    outmsg.Payload(new PayloadGSIStream(payload, ctx, logger, true));

    return MCC_Status(STATUS_OK);
  }
