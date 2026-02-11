writeTemp(BasicIo& tempIo, const byte* data, size_t size)
    {
        if (size == 0) return;
        if (tempIo.write(data, static_cast<long>(size)) != static_cast<long>(size)) {
            #ifndef SUPPRESS_WARNINGS
            EXV_WARNING << "Failed to write to temporary file.\n";
            #endif
            throw Error(21);
        }
    }
