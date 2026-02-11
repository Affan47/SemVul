killTimers()
{
 for (int i = 0; i < timerIds.size(); ++i)
 {
    killTimer(timerIds.at(i));
 }
 timerIds.clear();
}
