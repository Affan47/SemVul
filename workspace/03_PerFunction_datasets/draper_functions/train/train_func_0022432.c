formatDigitGroup(const QString &number, const QString &groupSeparator, const QString &decimalSeperator, QList<int> groupList) const
{
    if (groupList.isEmpty() || groupSeparator.isEmpty()) {
        return number;
    }

    QString num = number;
    int groupCount = groupList.count();
    int groupAt = 0;
    int groupSize = groupList.at(groupAt);
    int pos = num.indexOf(decimalSeperator);
    if (pos == -1) {
        pos = num.length();
    }
    pos = pos - groupSize;

    while (pos > 0 && groupSize > 0) {
        num.insert(pos, groupSeparator);
        if (groupAt + 1 < groupCount) {
            ++groupAt;
            groupSize = groupList.at(groupAt);
        }
        pos = pos - groupSize;
    }

    return num;
}
