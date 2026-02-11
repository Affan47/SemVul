setBackground(QWidget *widget, const QColor &color)
{
    QPalette palette = widget->palette();
    palette.setColor(widget->backgroundRole(), color);
    widget->setPalette(palette);

    QString name = color.name();
    name += " (" + QString::number(color.red()) + ", "
                 + QString::number(color.green()) + ", "
                 + QString::number(color.blue()) + ")";
    widget->setToolTip(name);
}
