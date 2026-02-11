setData(TMSettings *settings)
{
    root->clear();

    foreach (SummaryMetrics rideMetrics, *(settings->data)) {


        if (main->isfiltered && !main->filters.contains(rideMetrics.getFileName())) continue;

        double value = rideMetrics.getForSymbol(settings->symbol);
        QString text1 = rideMetrics.getText(settings->field1, "(unknown)");
        QString text2 = rideMetrics.getText(settings->field2, "(unknown)");
        if (text1 == "") text1 = "(unknown)";
        if (text2 == "") text2 = "(unknown)";

        TreeMap *first = root->insert(text1, 0.0);
        first->insert(text2, value);
    }


    resizeEvent(NULL);
    repaint();
}
