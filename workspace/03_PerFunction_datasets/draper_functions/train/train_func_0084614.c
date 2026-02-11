GetUDPVerifyKey(uint32_t targetIP)
{
	uint64_t buffer = (uint64_t)thePrefs::GetKadUDPKey() << 32 | targetIP;
	MD5Sum md5((const uint8_t *)&buffer, 8);
	return (uint32_t)(PeekUInt32(md5.GetRawHash()) ^ PeekUInt32(md5.GetRawHash() + 4) ^ PeekUInt32(md5.GetRawHash() + 8) ^ PeekUInt32(md5.GetRawHash() + 12)) % 0xFFFFFFFE + 1;
}
