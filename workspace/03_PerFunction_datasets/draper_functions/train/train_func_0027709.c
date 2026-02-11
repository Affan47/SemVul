addExtraOption(int opttype, TOpt::EOptionLayout layout, bool sendAlways) {
    SPtr<TOptionStatus> optStatus = new TOptionStatus();
    optStatus->OptionType = opttype;
    optStatus->Always = sendAlways;
    optStatus->Layout = layout;
    ExtraOpts.push_back(optStatus);
}
