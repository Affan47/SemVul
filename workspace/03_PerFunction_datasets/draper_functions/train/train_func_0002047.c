SeekTime(double timepos)
{
    double t = GetTime();
    if ((timepos - t) < 0.002 && (timepos - t) > -0.002 && timepos > 0.002)
    {

	return 0;
    }
    return ReadStream::SeekTime(timepos);
}
