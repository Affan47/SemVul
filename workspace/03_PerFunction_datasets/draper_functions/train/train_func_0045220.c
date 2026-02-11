dib9000_fw_component_bus_xfer(struct i2c_adapter *i2c_adap, struct i2c_msg msg[], int num)
{
	struct dib9000_state *state = i2c_get_adapdata(i2c_adap);
	u8 type = 0;
	u8 port = DIBX000_I2C_INTERFACE_GPIO_3_4;
	u16 scl = state->component_bus_speed;
	struct dib9000_fe_memory_map *m = &state->platform.risc.fe_mm[FE_MM_RW_COMPONENT_ACCESS_BUFFER];
	u8 p[13] = { 0 };

	p[0] = type;
	p[1] = port;
	p[2] = msg[0].addr << 1;

	p[3] = (u8) scl & 0xff;
	p[4] = (u8) (scl >> 8);

	p[7] = 0;
	p[8] = 0;

	p[9] = (u8) (msg[0].len);
	p[10] = (u8) (msg[0].len >> 8);
	if ((num > 1) && (msg[1].flags & I2C_M_RD)) {
		p[11] = (u8) (msg[1].len);
		p[12] = (u8) (msg[1].len >> 8);
	} else {
		p[11] = 0;
		p[12] = 0;
	}

	if (mutex_lock_interruptible(&state->platform.risc.mem_mbx_lock) < 0) {
		dprintk("could not get the lock");
		return 0;
	}

	dib9000_risc_mem_write(state, FE_MM_W_COMPONENT_ACCESS, p);

	{
		dib9000_risc_mem_setup_cmd(state, m->addr, msg[0].len, 0);
		dib9000_risc_mem_write_chunks(state, msg[0].buf, msg[0].len);
	}


	if (dib9000_fw_memmbx_sync(state, FE_SYNC_COMPONENT_ACCESS) < 0) {
		mutex_unlock(&state->platform.risc.mem_mbx_lock);
		return 0;
	}


	if ((num > 1) && (msg[1].flags & I2C_M_RD))
		dib9000_risc_mem_read(state, FE_MM_RW_COMPONENT_ACCESS_BUFFER, msg[1].buf, msg[1].len);

	mutex_unlock(&state->platform.risc.mem_mbx_lock);

	return num;
}
