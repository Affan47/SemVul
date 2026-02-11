RandomInteger(int min, int max)
{
    if (! generator_initialised)
    {
	InitialiseRandomNumberGenerator();
    }
#ifdef MS_WINDOWS
    return min + rand() % (max - min + 1);
#else
    return min + random() % (max - min + 1);
#endif
}
