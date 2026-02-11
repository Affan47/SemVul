GetCurBtnColor(const QPushButton* btn)
{
    QColor color;

    if (mSettings != NULL)
    {
        if (btn == mRowHColorBgBtn)
        {
            color.setNamedColor(mSettings->mRowHColorBg);
        }
        else
        {
            color.setNamedColor(mSettings->mRowHColorFg);
        }
    }
    if (mSettings == NULL || !color.isValid())
    {
        if (btn == mRowHColorBgBtn)
        {
            color = QApplication::palette().color(QPalette::Active, QPalette::Button);
        }
        else
        {
            color = QApplication::palette().color(QPalette::Active, QPalette::ButtonText);
        }
    }

    return color;
}
