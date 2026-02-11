tabSelected(int index)
{

    if (active || currentStyle != 0) return;

    active = true;

    if (index >= 0) {
        charts[index]->show();
        charts[index]->setProperty("ride", property("ride"));
        charts[index]->setProperty("dateRange", property("dateRange"));
        controlStack->setCurrentIndex(index);
        titleEdit->setText(charts[index]->property("title").toString());
    }

    active = false;
}
