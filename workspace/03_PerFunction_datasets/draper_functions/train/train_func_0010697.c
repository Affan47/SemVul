applyShortYearWindow(int inputYear) const
{
    if (inputYear >= 0 && inputYear <= 99) {
        int shortStartYear = m_shortYearWindowStartYear % 100;
        int yearOffset = m_shortYearWindowStartYear - shortStartYear;
        if (inputYear >= shortStartYear) {
            return inputYear + yearOffset;
        } else {
            return inputYear + yearOffset + 100;
        }
    } else {
        return inputYear;
    }
}
