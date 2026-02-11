CallProcessCallback()
{
    return (fProcess != NULL) ? fProcess(GetEngineControl()->fBufferSize, fProcessArg) : 0;
}
