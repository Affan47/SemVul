sidebarFontPalette(const QPalette &original)
{
    QPalette palette = original;
    palette.setColor(QPalette::Active, QPalette::Text, panelTextColor());
    palette.setColor(QPalette::Active, QPalette::WindowText, panelTextColor());
    palette.setColor(QPalette::Inactive, QPalette::Text, panelTextColor().darker());
    palette.setColor(QPalette::Inactive, QPalette::WindowText, panelTextColor().darker());
    return palette;
}
