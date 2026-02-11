initScalar(double min_value, double max_value)
{
    g_assert(_unit_menu != NULL);
    Scalar::setDigits(_unit_menu->getDefaultDigits());
    Scalar::setIncrements(_unit_menu->getDefaultStep(),
                          _unit_menu->getDefaultPage());
    Scalar::setRange(min_value, max_value);
}
