isValid(const QTime &time) const
{
    if (isValid()) {
        if (periodStart() <= periodEnd()) {
            return time >= periodStart() && time <= periodEnd();
        } else {
            return ((time >= periodStart() && time <= QTime(23, 59, 59, 999)) ||
                    (time >= QTime(0, 0, 0) && time <= periodEnd()));
        }
    } else {
        return false;
    }
}
