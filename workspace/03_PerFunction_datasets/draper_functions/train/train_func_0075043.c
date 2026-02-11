sshv2_response_return_code (gftp_request * request, sshv2_message * message,
                            unsigned int ret)
{
  switch (ret)
    {
      case SSH_FX_OK:
      case SSH_FX_EOF:
      case SSH_FX_NO_SUCH_FILE:
      case SSH_FX_FAILURE:
      case SSH_FX_OP_UNSUPPORTED:
        return (GFTP_ERETRYABLE);
      case SSH_FX_PERMISSION_DENIED:
        return (GFTP_EFATAL);
      default:
        return (sshv2_wrong_response (request, message));
    }
}
