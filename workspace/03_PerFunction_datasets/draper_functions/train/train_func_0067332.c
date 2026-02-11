meanMaxAggregate(QVector<double> &into, QVector<double> &other, QVector<QDate>&dates, QDate rideDate)
{
    if (into.size() < other.size()) {
        into.resize(other.size());
        dates.resize(other.size());
    }

    for (int i=0; i<other.size(); i++)
        if (other[i] > into[i]) {
            into[i] = other[i];
            dates[i] = rideDate;
        }
}
