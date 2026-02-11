tick (double dtime)
{
    if (!removed) {
        timeleft -= dtime;
        if (repeatp) {
            while (timeleft <= 0) {
                handler->alarm();
                timeleft += interval;
            }
        } else if (timeleft <= 0) {
            handler->alarm();
        }
    }
}
