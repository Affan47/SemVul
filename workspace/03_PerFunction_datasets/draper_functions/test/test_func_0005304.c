Frames2Time(jack_nframes_t frames, jack_nframes_t buffer_size)
{
    if (fInitialized) {


        int32_t df = frames - fFrames;
        int64_t dp = fNextWakeUp - fCurrentWakeup;
        return fCurrentWakeup + (int64_t)rint((double) df * (double) dp / buffer_size);
    } else {
        return 0;
    }
}
