setBad(QStringList errors)
{
    QPalette pal;
    pal.setColor(QPalette::Text, Qt::red);
    setPalette(pal);

    setToolTip(errors.join(" and "));
}
