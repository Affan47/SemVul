operator==(const DateTimeRule& that) const {
    return ((this == &that) ||
            (getDynamicClassID() == that.getDynamicClassID() &&
            fMonth == that.fMonth &&
            fDayOfMonth == that.fDayOfMonth &&
            fDayOfWeek == that.fDayOfWeek &&
            fWeekInMonth == that.fWeekInMonth &&
            fMillisInDay == that.fMillisInDay &&
            fDateRuleType == that.fDateRuleType &&
            fTimeRuleType == that.fTimeRuleType));
}
