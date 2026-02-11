get_resource_name_by_board_type(enum swan_board_type type)
{
	if (swan_package_flags & SWAN_FLAGS_MODEM_UPGRADE)
	{
		return MODEM_RESOURCE_NAME;
	}

	switch (type)
	{
	case SWAN_BOARD_I200:
		return I200_RESOURCE_NAME;

	case SWAN_BOARD_I600:
		return I600_RESOURCE_NAME;

	case SWAN_BOARD_I700:
		return I700_RESOURCE_NAME;

	default:
		return RESOURCE_IMAGE_NAME;
	}
}
