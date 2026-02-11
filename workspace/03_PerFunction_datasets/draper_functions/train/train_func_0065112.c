initialiseSymbol() {
    int i;

    for(i = 0; i < MAX_SYMBOL_ENUM; i++)
        if(symbol_values[i] != newUtf8(symbol_values[i])) {
            jam_fprintf(stderr, "Error when initialising VM symbols."
                                "  Aborting VM.\n");
            return FALSE;
        }

    return TRUE;
}
