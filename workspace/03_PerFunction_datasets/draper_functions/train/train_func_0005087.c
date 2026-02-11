ooSocketBind (OOSOCKET socket, OOIPADDR addr, int port)
{
   struct ast_sockaddr m_addr;

   memset(&m_addr, 0, sizeof(m_addr));


   if (socket == OOSOCKET_INVALID)
   {
      OOTRACEERR1("Error:Invalid socket passed to bind\n");
      return ASN_E_INVSOCKET;
   }

   ast_sockaddr_copy(&m_addr, &addr);
   ast_sockaddr_set_port(&m_addr, port);

   if (ast_bind(socket, &m_addr) < 0) {
      if (errno != EADDRINUSE) {
      	perror ("bind");
      	OOTRACEERR2("Error:Bind failed, error: %d\n", errno);
      }
      return ASN_E_INVSOCKET;
   }

   return ASN_OK;
}
