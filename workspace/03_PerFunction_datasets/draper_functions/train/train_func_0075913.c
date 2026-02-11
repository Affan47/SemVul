sshv2_wrong_response (gftp_request * request, sshv2_message * message)
{
  request->logging_function (gftp_logging_error, request,
                     _("Received wrong response from server, disconnecting\n"));
  gftp_disconnect (request);

  if (message != NULL)
    sshv2_message_free (message);

  return (GFTP_EFATAL);
}
