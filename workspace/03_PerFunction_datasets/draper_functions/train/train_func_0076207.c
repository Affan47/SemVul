compute(const RideFile *, const Zones *, int,
                 const HrZones *, int,
                 const QHash<QString,RideMetric*> &deps,
                 const MainWindow *) {

        PeakWPK5m *wpk5m = dynamic_cast<PeakWPK5m*>(deps.value("5m_peak_wpk"));
        setValue(wpk5m->value(false) * 12 + 3.5);
        setCount(1);
    }
