Update( void)
{
    float newTime = Timer::getTime();
    _count++;

    if( (newTime-_oldTime) > _period)
    {
	_cpp = ((float)_count)/(newTime-_oldTime);
	_count = 0;
	_oldTime = newTime;
    }
}
