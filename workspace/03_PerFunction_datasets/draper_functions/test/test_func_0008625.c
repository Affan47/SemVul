_setColor(const QColor &color, const QString &name)
{
    if (color.isValid()) {
        if (cbDefaultColor && cbDefaultColor->isChecked())
            cbDefaultColor->setChecked(false);
        selColor = color;
    } else {
        if (cbDefaultColor && cbDefaultColor->isChecked())
            cbDefaultColor->setChecked(true);
        selColor = defaultColor;
    }

    showColor(selColor, name);

    emit q->colorSelected(selColor);
}
