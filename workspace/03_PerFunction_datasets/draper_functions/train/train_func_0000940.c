deleteRules(void) {
    delete fInitialRule;
    fInitialRule = NULL;
    if (fHistoricRules != NULL) {
        while (!fHistoricRules->isEmpty()) {
            delete (TimeZoneRule*)(fHistoricRules->orphanElementAt(0));
        }
        delete fHistoricRules;
        fHistoricRules = NULL;
    }
    if (fFinalRules != NULL) {
        while (!fFinalRules->isEmpty()) {
            delete (AnnualTimeZoneRule*)(fFinalRules->orphanElementAt(0));
        }
        delete fFinalRules;
        fFinalRules = NULL;
    }
}
