add_offloaded_reg(struct vub300_mmc_host *vub300,
			      struct offload_registers_access *register_access)
{
	u32 Register = ((0x03 & register_access->command_byte[0]) << 15)
			| ((0xFF & register_access->command_byte[1]) << 7)
			| ((0xFE & register_access->command_byte[2]) >> 1);
	u8 func = ((0x70 & register_access->command_byte[0]) >> 4);
	u8 regs = vub300->dynamic_register_count;
	u8 i = 0;
	while (0 < regs-- && 1 == vub300->sdio_register[i].activate) {
		if (vub300->sdio_register[i].func_num == func &&
		    vub300->sdio_register[i].sdio_reg == Register) {
			if (vub300->sdio_register[i].prepared == 0)
				vub300->sdio_register[i].prepared = 1;
			vub300->sdio_register[i].response =
				register_access->Respond_Byte[2];
			vub300->sdio_register[i].regvalue =
				register_access->Respond_Byte[3];
			return;
		} else {
			i += 1;
			continue;
		}
	}
	__add_offloaded_reg_to_fifo(vub300, register_access, func);
}
