Finalize()
{
    uint32 length = 0;
    HMAC_Final(&m_ctx, (uint8*)m_digest, (unsigned int*)&length);
    ASSERT(length == SHA_DIGEST_LENGTH)
}
