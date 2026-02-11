metricDetails(QString symbol)
{
    for(int i = 0; i < metrics.count(); i++)
        if (metrics[i].symbol == symbol)
            return &metrics[i];
    return NULL;
}
