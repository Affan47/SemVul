RestartTime(void)
{
    if(time_stopped)
    {
        mytimer temp;

        temp=Timer();

        EndTime += (temp - StopTimeVal);
        StartGameTime += (temp - StopTimeVal);
        time_stopped = FALSE;
    }
}
