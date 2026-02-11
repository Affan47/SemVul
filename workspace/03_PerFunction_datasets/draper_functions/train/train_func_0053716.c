setMinimalDaysInFirstWeek(uint8_t value)
{


    if (value < 1) {
        value = 1;
    } else if (value > 7) {
        value = 7;
    }
    if (fMinimalDaysInFirstWeek != value) {
        fMinimalDaysInFirstWeek = value;
        fAreFieldsSet = FALSE;
    }
}
