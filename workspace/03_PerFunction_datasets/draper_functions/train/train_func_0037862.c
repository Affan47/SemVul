ProcessGraphAsyncSlave()
{
    if (ResumeRefNum() < 0) {
        jack_error("JackAudioDriver::ProcessGraphAsyncSlave: ResumeRefNum error");
    }
}
