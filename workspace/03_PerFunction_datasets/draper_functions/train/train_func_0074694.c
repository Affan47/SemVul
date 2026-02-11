addAllHrZones() {
    RideMetricFactory::instance().addMetric(HrZoneTime1());
    RideMetricFactory::instance().addMetric(HrZoneTime2());
    RideMetricFactory::instance().addMetric(HrZoneTime3());
    RideMetricFactory::instance().addMetric(HrZoneTime4());
    RideMetricFactory::instance().addMetric(HrZoneTime5());
    RideMetricFactory::instance().addMetric(HrZoneTime6());
    RideMetricFactory::instance().addMetric(HrZoneTime7());
    RideMetricFactory::instance().addMetric(HrZoneTime8());
    return true;
}
