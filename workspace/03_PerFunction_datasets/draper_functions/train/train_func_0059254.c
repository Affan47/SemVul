lps25hPressureToAltitude(float* pressure)
{
    if (*pressure > 0)
    {


        return ((powf((1015.7f / *pressure), CONST_PF) - 1.0f) * (FIX_TEMP + 273.15f)) / 0.0065f;
    }
    else
    {
        return 0;
    }
}
