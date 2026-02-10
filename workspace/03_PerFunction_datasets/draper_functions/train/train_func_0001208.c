isSingleOrLead(const int32_t (*stateTable)[256], uint8_t state, UBool isDBCSOnly, uint8_t b) {
    const int32_t *row=stateTable[state];
    int32_t entry=row[b];
    if(MBCS_ENTRY_IS_TRANSITION(entry)) {
        return hasValidTrailBytes(stateTable, (uint8_t)MBCS_ENTRY_TRANSITION_STATE(entry));
    } else {
        uint8_t action=(uint8_t)(MBCS_ENTRY_FINAL_ACTION(entry));
        if(action==MBCS_STATE_CHANGE_ONLY && isDBCSOnly) {
            return FALSE;
        } else {
            return action!=MBCS_STATE_ILLEGAL;
        }
    }
}
