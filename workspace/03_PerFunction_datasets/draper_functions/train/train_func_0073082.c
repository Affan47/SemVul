linda_link_state_changed ( struct ib_device *ibdev ) {
	struct linda *linda = ib_get_drvdata ( ibdev );
	struct QIB_7220_IBCStatus ibcstatus;
	struct QIB_7220_EXTCtrl extctrl;
	unsigned int link_state;
	unsigned int link_width;
	unsigned int link_speed;


	linda_readq ( linda, &ibcstatus, QIB_7220_IBCStatus_offset );
	link_state = BIT_GET ( &ibcstatus, LinkState );
	link_width = BIT_GET ( &ibcstatus, LinkWidthActive );
	link_speed = BIT_GET ( &ibcstatus, LinkSpeedActive );
	DBGC ( linda, "Linda %p link state %s (%s %s)\n", linda,
	       linda_link_state_text ( link_state ),
	       ( link_speed ? "DDR" : "SDR" ), ( link_width ? "x4" : "x1" ) );


	linda_readq ( linda, &extctrl, QIB_7220_EXTCtrl_offset );
	BIT_SET ( &extctrl, LEDPriPortGreenOn,
		  ( ( link_state >= LINDA_LINK_STATE_INIT ) ? 1 : 0 ) );
	BIT_SET ( &extctrl, LEDPriPortYellowOn,
		  ( ( link_state >= LINDA_LINK_STATE_ACTIVE ) ? 1 : 0 ) );
	linda_writeq ( linda, &extctrl, QIB_7220_EXTCtrl_offset );


	ibdev->port_state = ( link_state + 1 );
	ibdev->link_width_active =
		( link_width ? IB_LINK_WIDTH_4X : IB_LINK_WIDTH_1X );
	ibdev->link_speed_active =
		( link_speed ? IB_LINK_SPEED_DDR : IB_LINK_SPEED_SDR );
	ib_link_state_changed ( ibdev );
}
