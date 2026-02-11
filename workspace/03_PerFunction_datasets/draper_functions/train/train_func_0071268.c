appendAuthenticationOption(SPtr<TDUID> duid)
{

#ifndef MOD_DISABLE_AUTH
    if (!duid) {
        Log(Error) << "Auth: No duid! Probably internal error. Authentication option not appended." << LogEnd;
        return;
    }

    DigestType = SrvCfgMgr().getDigest();
    if (DigestType == DIGEST_NONE) {

        return;
    }

    Log(Debug) << "Auth: Setting DigestType to: " << this->DigestType << LogEnd;

    if (!getOption(OPTION_AUTH)) {
        SPtr<TAddrClient> client = SrvAddrMgr().getClient(duid);
        if (client && !client->getSPI() && this->getSPI())
            client->setSPI(this->getSPI());

        if (client)
            this->ReplayDetection = client->getNextReplayDetectionSent();
        else
            this->ReplayDetection = 1;
        Options.push_back(new TSrvOptAuthentication(this));
    }
#endif
}
