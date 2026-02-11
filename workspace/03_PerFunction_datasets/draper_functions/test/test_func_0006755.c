pkix_pl_LdapDefaultClient_Dispatch(
        PKIX_PL_LdapDefaultClient *client,
        void *plContext)
{
        PKIX_UInt32 bytesTransferred = 0;
        PKIX_Boolean keepGoing = PKIX_TRUE;

        PKIX_ENTER(LDAPDEFAULTCLIENT, "pkix_pl_LdapDefaultClient_Dispatch");
        PKIX_NULLCHECK_ONE(client);

        while (keepGoing) {
                switch (client->connectStatus) {
                case CONNECT_PENDING:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_ConnectContinue
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTCONNECTCONTINUEFAILED);
                        break;
                case CONNECTED:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_Bind
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTBINDFAILED);
                        break;
                case BIND_PENDING:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_BindContinue
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTBINDCONTINUEFAILED);
                        break;
                case BIND_RESPONSE:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_BindResponse
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTBINDRESPONSEFAILED);
                        break;
                case BIND_RESPONSE_PENDING:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_BindResponseContinue
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTBINDRESPONSECONTINUEFAILED);
                        break;
                case BOUND:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_Send
                                (client, &keepGoing, &bytesTransferred, plContext),
                                PKIX_LDAPDEFAULTCLIENTSENDFAILED);
                        break;
                case SEND_PENDING:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_SendContinue
                                (client, &keepGoing, &bytesTransferred, plContext),
                                PKIX_LDAPDEFAULTCLIENTSENDCONTINUEFAILED);
                        break;
                case RECV:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_Recv
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTRECVFAILED);
                        break;
                case RECV_PENDING:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_RecvContinue
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTRECVCONTINUEFAILED);
                        break;
                case RECV_INITIAL:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_RecvInitial
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTRECVINITIALFAILED);
                        break;
                case RECV_NONINITIAL:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_RecvNonInitial
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTRECVNONINITIALFAILED);
                        break;
                case ABANDON_PENDING:
                        PKIX_CHECK
                                (pkix_pl_LdapDefaultClient_AbandonContinue
                                (client, &keepGoing, plContext),
                                PKIX_LDAPDEFAULTCLIENTABANDONCONTINUEFAILED);
                        break;
                default:
                        PKIX_ERROR(PKIX_LDAPCERTSTOREINILLEGALSTATE);
                }
        }

cleanup:

        PKIX_RETURN(LDAPDEFAULTCLIENT);
}
