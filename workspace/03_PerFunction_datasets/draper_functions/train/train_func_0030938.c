start_iauth_query(struct AuthRequest *auth)
{
  FlagSet(&auth->flags, AR_IAUTH_PENDING);
  if (!sendto_iauth(auth->client, "C %s %hu %s %hu",
                    cli_sock_ip(auth->client), auth->port,
                    ircd_ntoa(&auth->local.addr), auth->local.port))
    FlagClr(&auth->flags, AR_IAUTH_PENDING);
}
