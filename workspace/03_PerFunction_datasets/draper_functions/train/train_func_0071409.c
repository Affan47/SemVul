deleteSeries(RideFile::SeriesType series)
{


    if (anomalies.count()) {
        QMutableMapIterator <QString, QString> a(anomalies);
        QMap<QString,QString> newa;
        while (a.hasNext()) {
            a.next();

            int crow;
            RideFile::SeriesType cseries;
            unxsstring(a.key(), crow, cseries);

            if (cseries == series) {

                ;
            } else {
                newa.insert(a.key(), a.value());
            }
        }
        anomalies = newa;
    }


    if (found.count()) {
        QMutableMapIterator <QString, QString> r(found);
        QMap<QString,QString> newr;
        while (r.hasNext()) {
            r.next();

            int crow;
            RideFile::SeriesType cseries;
            unxsstring(r.key(), crow, cseries);

            if (cseries == series) {

                ;
            } else {
                newr.insert(r.key(), r.value());
            }
        }
        found = newr;
    }
}
