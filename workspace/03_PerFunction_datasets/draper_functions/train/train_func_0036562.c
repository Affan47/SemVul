pvr2_led_ctrl(struct pvr2_hdw *hdw,int onoff)
{
	unsigned int scheme_id;
	led_method_func fp;

	if ((!onoff) == (!hdw->led_on)) return;

	hdw->led_on = onoff != 0;

	scheme_id = hdw->hdw_desc->led_scheme;
	if (scheme_id < ARRAY_SIZE(led_methods)) {
		fp = led_methods[scheme_id];
	} else {
		fp = NULL;
	}

	if (fp) (*fp)(hdw,onoff);
}
