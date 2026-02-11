metricToggled(bool x)
{
    if (active) return;

    active = true;
    stale = true;
    data->setChecked(!x);
    switchMode();
    active = false;
}
