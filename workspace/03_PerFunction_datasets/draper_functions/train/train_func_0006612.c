operator/=(float fScalar)
{
    if ( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f/fScalar;
        x *= fInvScalar;
        y *= fInvScalar;
    }
    else
    {
        x = FLT_MAX;
        y = FLT_MAX;
    }

    return *this;
}
