SetBufferSize(jack_nframes_t buffer_size)
{
    jack_log("JackServer::SetBufferSize nframes = %ld", buffer_size);
    jack_nframes_t current_buffer_size = fEngineControl->fBufferSize;

    if (current_buffer_size == buffer_size) {
        jack_log("SetBufferSize: requirement for new buffer size equals current value");
        return 0;
    }

    if (fAudioDriver->IsFixedBufferSize()) {
        jack_log("SetBufferSize: driver only supports a fixed buffer size");
        return -1;
    }

    if (fAudioDriver->Stop() != 0) {
        jack_error("Cannot stop audio driver");
        return -1;
    }

    if (fAudioDriver->SetBufferSize(buffer_size) == 0) {
        fEngine->NotifyBufferSize(buffer_size);
        return fAudioDriver->Start();
    } else {
        jack_error("Cannot SetBufferSize for audio driver, restore current value %ld", current_buffer_size);
        fAudioDriver->SetBufferSize(current_buffer_size);
        fAudioDriver->Start();

        return -1;
    }
}
