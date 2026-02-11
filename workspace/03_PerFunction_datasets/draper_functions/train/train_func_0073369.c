powtodb( double f )
{
    if( f <= 0 ) return (0);
    else
    {
        double val = 100 + 10./LOGTEN * log(f);
        return (val < 0 ? 0 : val);
    }
}
