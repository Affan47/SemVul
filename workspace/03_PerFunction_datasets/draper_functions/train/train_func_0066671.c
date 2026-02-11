write(unsigned char* buffer)
{
    fAgeInstanceId.write(buffer);
    buffer += 16;

    plString::Wide wsbuf = fAgeFilename.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 64 ? 63 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[63 * sizeof(pl_wchar_t)] = 0;
    buffer += 64 * sizeof(pl_wchar_t);

    wsbuf = fAgeInstanceName.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 64 ? 63 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[63 * sizeof(pl_wchar_t)] = 0;
    buffer += 64 * sizeof(pl_wchar_t);

    wsbuf = fAgeUserName.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 64 ? 63 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[63 * sizeof(pl_wchar_t)] = 0;
    buffer += 64 * sizeof(pl_wchar_t);

    wsbuf = fDescription.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 1024 ? 1023 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[1023 * sizeof(pl_wchar_t)] = 0;
    buffer += 1024 * sizeof(pl_wchar_t);

    *(uint32_t*)buffer = fSequenceNumber;
    buffer += sizeof(uint32_t);

    *(uint32_t*)buffer = fLanguage;
    buffer += sizeof(uint32_t);

    *(uint32_t*)buffer = fPopulation;
    buffer += sizeof(uint32_t);

    *(uint32_t*)buffer = fCurrPopulation;
    buffer += sizeof(uint32_t);
}
