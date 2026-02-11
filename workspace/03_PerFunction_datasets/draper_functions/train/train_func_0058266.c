le_addr_type(uint8_t bdaddr_type)
{
	switch (bdaddr_type) {
	case LE_RANDOM_ADDRESS:
		return BDADDR_LE_RANDOM;
	case LE_PUBLIC_ADDRESS:
	default:
		return BDADDR_LE_PUBLIC;
	}
}
