setCurrentValue(double value)
    {
        if (value != d_currentValue)
        {

            value = ceguimax(ceguimin(value, d_maxValue), d_minValue);

            d_currentValue = value;

            WindowEventArgs args(this);
            onValueChanged(args);
        }
    }
