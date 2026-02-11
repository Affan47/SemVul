radeon_i2c_lookup(struct radeon_device *rdev,
					  struct radeon_i2c_bus_rec *i2c_bus)
{
	int i;

	for (i = 0; i < RADEON_MAX_I2C_BUS; i++) {
		if (rdev->i2c_bus[i] &&
		    (rdev->i2c_bus[i]->rec.i2c_id == i2c_bus->i2c_id)) {
			return rdev->i2c_bus[i];
		}
	}
	return NULL;
}
