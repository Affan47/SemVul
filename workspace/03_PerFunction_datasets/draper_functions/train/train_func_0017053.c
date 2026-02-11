Speed( void ) const
{
    REAL ret = verletSpeed_ + .5f * lastTimestep_ * acceleration;
    return ret > 0 ? ret : 0;
}
