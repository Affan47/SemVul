AddMessage(int level, const char *message)
{
    if (fGuard.Trylock()) {
        fBuffers[fInBuffer].level = level;
        strncpy(fBuffers[fInBuffer].message, message, MB_BUFFERSIZE);
        fInBuffer = MB_NEXT(fInBuffer);
        fGuard.Signal();
        fGuard.Unlock();
    } else {
        INC_ATOMIC(&fOverruns);
    }
}
