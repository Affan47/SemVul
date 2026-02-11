layoutButtons(QList<ButtonItem *> buttons, const QRect & frameRect) const
{
    double x[] = { 0.92, 0.84, 0.95, 0.93, 0.84, 0.5, 0.80 };
    double y[] = { 0.22, 0.15, 0.33, 0.44, 0.55, 0.17, 0.45 };
    for ( int i = 0; i < buttons.size() && i < 7; i++ ) {

        QGraphicsItem * button = buttons[ i ];
        button->setPos( frameRect.left() + (int)((float)frameRect.width() * x[i]),
                frameRect.top() + (int)((float)frameRect.height() * y[i]));
    }
}
