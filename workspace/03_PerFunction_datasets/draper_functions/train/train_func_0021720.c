getMaxValid() {
    unsigned long maxValid=0;
    SPtr<TOpt> ptrOpt;
    SubOptions.first();
    while (ptrOpt=SubOptions.get())
    {
        if (ptrOpt->getOptType()==OPTION_IAADDR) {
            SPtr<TOptIAAddress> ptrIAAddr=(Ptr*)ptrOpt;
            if (maxValid<ptrIAAddr->getValid())
                maxValid=ptrIAAddr->getValid();
        }
    }
    return maxValid;
}
