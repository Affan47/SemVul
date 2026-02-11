SpinControlWidth(txt_spincontrol_t *spincontrol)
{
    unsigned int minw, maxw;

    switch (spincontrol->type)
    {
        case TXT_SPINCONTROL_FLOAT:
            minw = FloatWidth(spincontrol->min.f, spincontrol->step.f);
            maxw = FloatWidth(spincontrol->max.f, spincontrol->step.f);
            break;

        default:
        case TXT_SPINCONTROL_INT:
            minw = IntWidth(spincontrol->min.i);
            maxw = IntWidth(spincontrol->max.i);
            break;

    }


    if (minw > maxw)
    {
        return minw;
    }
    else
    {
        return maxw;
    }
}
