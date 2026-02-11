drv_CW_process_input(void)
{
    while (RingRPos != RingWPos) {
	drv_generic_keypad_press(RingBuffer[RingRPos++]);
	if (RingRPos >= sizeof(RingBuffer))
	    RingRPos = 0;
    }
}
