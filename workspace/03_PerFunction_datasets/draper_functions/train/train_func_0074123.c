setRoundingIncrement(double newValue) {
    if (newValue > 0.0) {
        if (fRoundingIncrement == NULL) {
            fRoundingIncrement = new DigitList();
        }
        if (fRoundingIncrement != NULL) {
            fRoundingIncrement->set(newValue);
            return;
        }
    }


    delete fRoundingIncrement;
    fRoundingIncrement = NULL;
}
