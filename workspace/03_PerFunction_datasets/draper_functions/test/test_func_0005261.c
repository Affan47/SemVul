ip_ok(uint32_t ip)
{
    uint8_t ip_hi = (uint8_t)ip;

    if (ip == 0xffffffff ||
	ip_hi == 0 ||
	ip_hi == 127 ||
	(ip_hi & 240) == 224)
	return false;

    return true;
}
