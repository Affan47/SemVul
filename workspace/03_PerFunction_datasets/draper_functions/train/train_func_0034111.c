foreground() const
{
    return KStatefulBrush(KColorScheme::Tooltip,
                          KColorScheme::NormalText)
    .brush(QPalette::Active).color();
}
