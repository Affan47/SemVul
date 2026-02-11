writeChartXML(QDir home, QList<LTMSettings> charts)
{
    LTMChartParser::serialize(QString(home.path() + "/charts.xml"), charts);
}
