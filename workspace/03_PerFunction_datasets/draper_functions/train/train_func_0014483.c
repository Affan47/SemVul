operator=(const AnnualTimeZoneRule& right) {
    if (this != &right) {
        TimeZoneRule::operator=(right);
        delete fDateTimeRule;
        fDateTimeRule = right.fDateTimeRule->clone();
        fStartYear = right.fStartYear;
        fEndYear = right.fEndYear;
    }
    return *this;
}
