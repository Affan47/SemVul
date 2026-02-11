closeWindow(GcWindow*thisone)
{
    if (charts.contains(thisone)) removeChart(charts.indexOf(thisone));
}
