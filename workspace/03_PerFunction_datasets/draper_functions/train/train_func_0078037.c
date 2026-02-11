get_link_speed_and_width(struct ocrdma_dev *dev,
					    u8 *ib_speed, u8 *ib_width)
{
	int status;
	u8 speed;

	status = ocrdma_mbx_get_link_speed(dev, &speed, NULL);
	if (status)
		speed = OCRDMA_PHYS_LINK_SPEED_ZERO;

	switch (speed) {
	case OCRDMA_PHYS_LINK_SPEED_1GBPS:
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
		break;

	case OCRDMA_PHYS_LINK_SPEED_10GBPS:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_1X;
		break;

	case OCRDMA_PHYS_LINK_SPEED_20GBPS:
		*ib_speed = IB_SPEED_DDR;
		*ib_width = IB_WIDTH_4X;
		break;

	case OCRDMA_PHYS_LINK_SPEED_40GBPS:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_4X;
		break;

	default:

		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
	}
}
