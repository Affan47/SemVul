FixRfmModule(void)
{
    RfmModule save;

    save = RFM_ModuleCurrent;
    for (RFM_ModuleCurrent = RFM_ModuleTop;
         RFM_ModuleCurrent != NULL;
         RFM_ModuleCurrent = RFM_ModuleCurrent->next) {
        RFM_ModuleCurrent->entry = RFM_ModuleCurrent->func->entry;
        FixRfmTemp();
        FixRfmLabel();
        FixRfmBlock();
    }
    RFM_ModuleCurrent = save;
}
