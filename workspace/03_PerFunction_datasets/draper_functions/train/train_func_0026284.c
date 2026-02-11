setCurrentDateTime()
{

    time_t tt = time(NULL);
    return Date.setCurrentDate(tt) && Time.setCurrentTime(tt);
}
