dataToDoubles()
{
    uint8_t aBytes[8];

    for (int i = PACKET_HEADER_LEN; i<_packv.size()-7; ++i)
    {

        for (int j = 0; j<8; ++j)
        {
            aBytes[j] = _packv[i+j];
        }

        _dataDoubles.push_back(doubleFromBytes(aBytes));
    }
}
