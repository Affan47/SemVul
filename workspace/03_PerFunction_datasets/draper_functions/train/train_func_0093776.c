UpdateParams(int active_ports)
    {
        if (active_ports == 0) {
            fSubPeriodSize = fPeriodSize;
        } else {
            jack_nframes_t period = (int) powf(2.f, (int)(log(float(fPacketSize) / (active_ports * sizeof(sample_t))) / log(2.)));
            fSubPeriodSize = (period > fPeriodSize) ? fPeriodSize : period;
        }

        fSubPeriodBytesSize = fSubPeriodSize * sizeof(sample_t) + sizeof(int);
        fNumPackets = fPeriodSize / fSubPeriodSize;
    }
