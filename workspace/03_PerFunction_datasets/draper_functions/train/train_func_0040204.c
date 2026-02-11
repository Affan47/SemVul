updateMetrics()
{
    QVector<QPair<QString,QString> > data;
    QwtArray<double> x;
    QwtArray<double> y;

    we->rawData(data);

    int curSecs = 0;

    QSharedPointer<RideFile> workout(new RideFile());
    workout->mainwindow = hackMW;
    workout->setRecIntSecs(1);
    double curMin = 0;
    for(int i = 0; i < data.size() ; i++)
    {
        if(data[i].first == "LAP") continue;

        double min = data[i].first.toDouble();
        double watts = data[i].second.toDouble();
        int secs = min * 60;
        for(int j = 0; j < secs; j++)
        {
            RideFilePoint rfp;
            rfp.secs = curSecs++;
            rfp.watts = watts;
            rfp.cad = 90;
            workout->appendPoint(rfp);
        }

        x.append(curMin);
        y.append(watts);
        curMin += min;
        x.append(curMin);
        y.append(watts);

    }

    plot->setAxisAutoScale(QwtPlot::yLeft);
    plot->setAxisAutoScale(QwtPlot::xBottom);
    plot->setData(x,y);
    plot->replot();


    const RideMetricFactory &factory = RideMetricFactory::instance();
    const RideMetric *rm = factory.rideMetric("skiba_xpower");
    QStringList metrics;
    metrics.append("time_riding");
    metrics.append("total_work");
    metrics.append("average_power");
    metrics.append("skiba_bike_score");
    metrics.append("skiba_xpower");
    QHash<QString,RideMetricPtr> results = rm->computeMetrics(NULL,&*workout,hackMW->zones(),hackMW->hrZones(),metrics);
    metricsSummary->updateMetrics(metrics,results);
}
