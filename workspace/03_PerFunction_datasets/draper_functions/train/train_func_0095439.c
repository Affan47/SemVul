ns1__executeCommand(soap* soap, char* command, char** result)
{

    if (!soap->userid || !soap->passwd)
    {
        DEBUG_LOG("MaNGOSsoap: Client didn't provide login information");
        return 401;
    }

    uint32 accountId = sAccountMgr.GetId(soap->userid);
    if (!accountId)
    {
        DEBUG_LOG("MaNGOSsoap: Client used invalid username '%s'", soap->userid);
        return 401;
    }

    if (!sAccountMgr.CheckPassword(accountId, soap->passwd))
    {
        DEBUG_LOG("MaNGOSsoap: invalid password for account '%s'", soap->userid);
        return 401;
    }

    if (sAccountMgr.GetSecurity(accountId) < SEC_ADMINISTRATOR)
    {
        DEBUG_LOG("MaNGOSsoap: %s's gmlevel is too low", soap->userid);
        return 403;
    }

    if (!command || !*command)
        return soap_sender_fault(soap, "Command mustn't be empty", "The supplied command was an empty string");

    DEBUG_LOG("MaNGOSsoap: got command '%s'", command);
    SOAPCommand connection;


    {

        CliCommandHolder* cmd = new CliCommandHolder(accountId, SEC_CONSOLE, &connection, command, &SOAPCommand::print, &SOAPCommand::commandFinished);
        sWorld.QueueCliCommand(cmd);
    }


    int acc = connection.pendingCommands.acquire();
    if (acc)
    {
        sLog.outError("MaNGOSsoap: Error while acquiring lock, acc = %i, errno = %u", acc, errno);
    }


    char* printBuffer = soap_strdup(soap, connection.m_printBuffer.c_str());
    if (connection.hasCommandSucceeded())
    {
        *result = printBuffer;
        return SOAP_OK;
    }
    else
        return soap_sender_fault(soap, printBuffer, printBuffer);
}
