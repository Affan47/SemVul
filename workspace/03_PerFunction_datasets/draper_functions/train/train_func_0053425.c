hw20k2_i2c_lock_chip(struct hw *hw)
{

	hw_write_20kx(hw, I2C_IF_WLOCK, STATE_LOCKED);
	hw_write_20kx(hw, I2C_IF_WLOCK, STATE_LOCKED);
	if (hw_read_20kx(hw, I2C_IF_WLOCK) == STATE_LOCKED)
		return 0;

	return -1;
}
