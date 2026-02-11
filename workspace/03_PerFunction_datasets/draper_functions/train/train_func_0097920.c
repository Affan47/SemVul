natsemi_spi_read_bit ( struct bit_basher *basher,
				  unsigned int bit_id ) {
	struct natsemi_nic *natsemi = container_of ( basher, struct natsemi_nic,
						     spibit.basher );
	uint32_t mask = natsemi_eeprom_bits[bit_id];
	uint32_t reg;

	DBG_DISABLE ( DBGLVL_IO );
	reg = readl ( natsemi->regs + NATSEMI_MEAR );
	DBG_ENABLE ( DBGLVL_IO );
	return ( reg & mask );
}
