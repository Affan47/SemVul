Delete()
{
    jack_log("Jackdmp: delete server");


    std::map<std::string, JackDriverInfo*>::iterator it1;
    for (it1 = fSlavesList.begin(); it1 != fSlavesList.end(); it1++) {
        JackDriverInfo* info = (*it1).second;
        if (info) {
            fInstance->RemoveSlave((info));
            delete (info);
        }
    }
    fSlavesList.clear();


    std::map<std::string, int> ::iterator it2;
    for (it2 = fInternalsList.begin(); it2 != fInternalsList.end(); it2++) {
        int status;
        int refnum = (*it2).second;
        if (refnum > 0) {

            fInstance->GetEngine()->InternalClientUnload(refnum, &status);
        }
    }
    fInternalsList.clear();

    delete fInstance;
    fInstance = NULL;
}
