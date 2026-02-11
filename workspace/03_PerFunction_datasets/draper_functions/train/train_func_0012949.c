FFwdLap()
{
    if ((status&RT_RUNNING) == 0) return;

    double lapmarker;

    if (status&RT_MODE_ERGO) {
        lapmarker = ergFile->nextLap(load_msecs);
        if (lapmarker != -1) load_msecs = lapmarker;
        main->notifySeek(load_msecs);
    } else {
        lapmarker = ergFile->nextLap(displayWorkoutDistance*1000);
        if (lapmarker != -1) displayWorkoutDistance = lapmarker/1000;
    }
}
