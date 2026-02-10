drawAttenction()
{
    setMarkOpacity(1.0);
#if 0
    ANIMATE_PARAM(this, "backColor", 1000, QColor(255, 20, 20));
    ANIMATE_PARAM(this, "textColor", 1000, QColor(255, 255, 255));
#else
    ANIMATE_PARAM(this, "backColor", 1000, QApplication::palette().color(QPalette::Highlight));
    ANIMATE_PARAM(this, "textColor", 1000, QApplication::palette().color(QPalette::HighlightedText));
#endif
}
