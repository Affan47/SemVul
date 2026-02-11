addVam()
{
    QVector<QString> deps;
    deps.append("elevation_gain");
    deps.append("workout_time");
    RideMetricFactory::instance().addMetric(VAM(), &deps);
    return true;
}
