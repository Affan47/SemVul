ath5k_hw_set_ack_timeout(struct ath5k_hw *ah, unsigned int timeout)
{
	if (ath5k_hw_clocktoh(ah, AR5K_REG_MS(0xffffffff, AR5K_TIME_OUT_ACK))
			<= timeout)
		return -EINVAL;

	AR5K_REG_WRITE_BITS(ah, AR5K_TIME_OUT, AR5K_TIME_OUT_ACK,
		ath5k_hw_htoclock(ah, timeout));

	return 0;
}
