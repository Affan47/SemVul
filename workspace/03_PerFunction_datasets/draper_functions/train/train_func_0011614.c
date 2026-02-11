SMTP_auth_error(int sock, const char *msg)
{
    SockPrintf(sock, "*\r\n");
    SockRead(sock, smtp_response, sizeof(smtp_response) - 1);
    if (outlevel >= O_MONITOR) report(stdout, "%s", msg);
}
