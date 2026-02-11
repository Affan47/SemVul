host_drive_to_sdio_drive(int host_strength)
{
	switch (host_strength) {
	case MMC_SET_DRIVER_TYPE_A:
		return SDIO_DTSx_SET_TYPE_A;
	case MMC_SET_DRIVER_TYPE_B:
		return SDIO_DTSx_SET_TYPE_B;
	case MMC_SET_DRIVER_TYPE_C:
		return SDIO_DTSx_SET_TYPE_C;
	case MMC_SET_DRIVER_TYPE_D:
		return SDIO_DTSx_SET_TYPE_D;
	default:
		return SDIO_DTSx_SET_TYPE_B;
	}
}
