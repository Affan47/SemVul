AllocPorts()
    {
        int i;
        char name[32];
        jack_log("JackNetMaster::AllocPorts");


        for (i = 0; i < fParams.fSendAudioChannels; i++) {
            snprintf(name, sizeof(name), "to_slave_%d", i+1);
            if ((fAudioCapturePorts[i] = jack_port_register(fClient, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsTerminal, 0)) == NULL) {
                return -1;
            }
        }

        for (i = 0; i < fParams.fReturnAudioChannels; i++) {
            snprintf(name, sizeof(name), "from_slave_%d", i+1);
            if ((fAudioPlaybackPorts[i] = jack_port_register(fClient, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput | JackPortIsTerminal, 0)) == NULL) {
                return -1;
            }
        }


        for (i = 0; i < fParams.fSendMidiChannels; i++) {
            snprintf(name, sizeof(name), "midi_to_slave_%d", i+1);
            if ((fMidiCapturePorts[i] = jack_port_register(fClient, name, JACK_DEFAULT_MIDI_TYPE, JackPortIsInput | JackPortIsTerminal, 0)) == NULL) {
                return -1;
            }
        }

        for (i = 0; i < fParams.fReturnMidiChannels; i++) {
            snprintf(name, sizeof(name), "midi_from_slave_%d", i+1);
            if ((fMidiPlaybackPorts[i] = jack_port_register(fClient, name, JACK_DEFAULT_MIDI_TYPE,  JackPortIsOutput | JackPortIsTerminal, 0)) == NULL) {
                return -1;
            }
        }
        return 0;
    }
