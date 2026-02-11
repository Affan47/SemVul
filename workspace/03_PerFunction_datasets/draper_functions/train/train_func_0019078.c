set_link_state_by_speed(struct dummy_hcd *dum_hcd)
{
	struct dummy *dum = dum_hcd->dum;

	if (dummy_hcd_to_hcd(dum_hcd)->speed == HCD_USB3) {
		if ((dum_hcd->port_status & USB_SS_PORT_STAT_POWER) == 0) {
			dum_hcd->port_status = 0;
		} else if (!dum->pullup || dum->udc_suspended) {

			dum_hcd->port_status &= ~(USB_PORT_STAT_CONNECTION |
						USB_PORT_STAT_ENABLE);
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) != 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
		} else {

			dum_hcd->port_status |= (USB_PORT_STAT_CONNECTION |
						 USB_PORT_STAT_SPEED_5GBPS) ;
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) == 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
			if ((dum_hcd->port_status &
			     USB_PORT_STAT_ENABLE) == 1 &&
				(dum_hcd->port_status &
				 USB_SS_PORT_LS_U0) == 1 &&
				dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
				dum_hcd->active = 1;
		}
	} else {
		if ((dum_hcd->port_status & USB_PORT_STAT_POWER) == 0) {
			dum_hcd->port_status = 0;
		} else if (!dum->pullup || dum->udc_suspended) {

			dum_hcd->port_status &= ~(USB_PORT_STAT_CONNECTION |
						USB_PORT_STAT_ENABLE |
						USB_PORT_STAT_LOW_SPEED |
						USB_PORT_STAT_HIGH_SPEED |
						USB_PORT_STAT_SUSPEND);
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) != 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
		} else {
			dum_hcd->port_status |= USB_PORT_STAT_CONNECTION;
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) == 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
			if ((dum_hcd->port_status & USB_PORT_STAT_ENABLE) == 0)
				dum_hcd->port_status &= ~USB_PORT_STAT_SUSPEND;
			else if ((dum_hcd->port_status &
				  USB_PORT_STAT_SUSPEND) == 0 &&
					dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
				dum_hcd->active = 1;
		}
	}
}
