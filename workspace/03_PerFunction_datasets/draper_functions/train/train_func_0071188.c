closeAllWindows2() {


    bool did_close = true;
    QWidget *w;
    while((w = QApplication::activeModalWidget()) && did_close) {
        if(!w->isVisible())
            break;
        did_close = w->close();
    }
	if (!did_close) return;

    QWidgetList list = QApplication::topLevelWidgets();
    for (int i = 0; did_close && i < list.size(); ++i) {
        w = list.at(i);
        FritzingWindow *fWindow = qobject_cast<FritzingWindow *>(w);
		if (fWindow == NULL) continue;

        if (w->isVisible() && w->windowType() != Qt::Desktop) {
            did_close = w->close();
            list = QApplication::topLevelWidgets();
            i = -1;
        }
    }
	if (!did_close) return;

    list = QApplication::topLevelWidgets();
    for (int i = 0; did_close && i < list.size(); ++i) {
        w = list.at(i);
        if (w->isVisible() && w->windowType() != Qt::Desktop) {
            did_close = w->close();
            list = QApplication::topLevelWidgets();
            i = -1;
        }
    }

}
