Compile()
{
	uint32    w[80], i, a, b, c, d, e, t;


    for(i = 0; i < SHA1_BLOCK_SIZE / 4; ++i)
        w[i] = swap_b32(m_nBuffer[i]);

    for(i = SHA1_BLOCK_SIZE / 4; i < 80; ++i)
        w[i] = rotl32(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

    a = m_nHash[0];
    b = m_nHash[1];
    c = m_nHash[2];
    d = m_nHash[3];
    e = m_nHash[4];

    for(i = 0; i < 20; ++i)
    {
        rnd(ch, 0x5a827999);
    }

    for(i = 20; i < 40; ++i)
    {
        rnd(parity, 0x6ed9eba1);
    }

    for(i = 40; i < 60; ++i)
    {
        rnd(maj, 0x8f1bbcdc);
    }

    for(i = 60; i < 80; ++i)
    {
        rnd(parity, 0xca62c1d6);
    }

    m_nHash[0] += a;
    m_nHash[1] += b;
    m_nHash[2] += c;
    m_nHash[3] += d;
    m_nHash[4] += e;
}
