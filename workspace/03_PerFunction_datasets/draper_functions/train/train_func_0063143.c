Open(const char* server_name, const char* name, int uuid, jack_options_t options, jack_status_t* status)
{
    int result;
    jack_log("JackInternalClient::Open name = %s", name);

    if (strlen(name) >= JACK_CLIENT_NAME_SIZE) {
        jack_error("\"%s\" is too long to be used as a JACK client name.\n"
                   "Please use %lu characters or less",
                   name,
                   JACK_CLIENT_NAME_SIZE - 1);
        return -1;
    }

    strncpy(fServerName, server_name, sizeof(fServerName));


    char name_res[JACK_CLIENT_NAME_SIZE + 1];
    fChannel->ClientCheck(name, uuid, name_res, JACK_PROTOCOL_VERSION, (int)options, (int*)status, &result, false);
    if (result < 0) {
        int status1 = *status;
        if (status1 & JackVersionError) {
            jack_error("JACK protocol mismatch %d", JACK_PROTOCOL_VERSION);
        } else {
            jack_error("Client name = %s conflits with another running client", name);
        }
        goto error;
    }

    strcpy(fClientControl.fName, name_res);


    fChannel->ClientOpen(name_res, &fClientControl.fRefNum, &fEngineControl, &fGraphManager, this, &result);
    if (result < 0) {
        jack_error("Cannot open client name = %s", name_res);
        goto error;
    }

    SetupDriverSync(false);
    JackGlobals::fClientTable[fClientControl.fRefNum] = this;
    JackGlobals::fServerRunning = true;
    jack_log("JackInternalClient::Open name = %s refnum = %ld", name_res, fClientControl.fRefNum);
    return 0;

error:
    fChannel->Close();
    return -1;
}
