updateSelf(float elapsed)
{
    if (d_delay > 0 && d_started)
    {
        d_currentValue += elapsed;
        if (d_currentValue >= d_delay)
        {
            d_currentValue -= d_delay;
            CEGUI::WindowEventArgs args(this);
            fireEvent(EventTimerAlarm, args, EventNamespace);
        }
    }
}
