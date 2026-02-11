removeAlert(const AlertItem &alert)
{

    if (containsAlertUuid(alert.uuid())) {
        removeAlertUuid(alert.uuid());
        if (_widget) {
            QWidget *w = _buttons.value(alert.uuid());
            _buttons.remove(alert.uuid());
            for(int i=0; i < _widget->actions().count(); ++i) {
                if (_widget->widgetForAction(_widget->actions().at(i)) == w)
                    _widget->actions().at(i)->setVisible(false);
            }
        }
        _priorities.clear();
        for(int i = 0; i < alerts.count(); ++i) {
            _priorities << alerts.at(i).priority()*10000000 + i;
        }
        qSort(_priorities);
        if (_widget->sizePolicy().horizontalPolicy() != QSizePolicy::Expanding)
            _widget->adjustSize();
    }
    return true;
}
