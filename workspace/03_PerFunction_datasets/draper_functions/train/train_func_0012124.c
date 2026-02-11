EncryptSend(uint8* data, size_t len)
{
    if (!_initialized) { return; }
    if (len < CRYPTED_SEND_LEN) { return; }

    for (size_t t = 0; t < CRYPTED_SEND_LEN; t++)
    {
        _send_i %= _key.size();
        uint8 x = (data[t] ^ _key[_send_i]) + _send_j;
        ++_send_i;
        data[t] = _send_j = x;
    }
}
