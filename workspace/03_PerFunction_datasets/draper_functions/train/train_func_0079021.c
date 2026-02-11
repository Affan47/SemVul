ixgb_set_eeprom(struct net_device *netdev,
		  struct ethtool_eeprom *eeprom, u8 *bytes)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	struct ixgb_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	void *ptr;
	int max_len, first_word, last_word;
	u16 i;

	if (eeprom->len == 0)
		return -EINVAL;

	if (eeprom->magic != (hw->vendor_id | (hw->device_id << 16)))
		return -EFAULT;

	max_len = ixgb_get_eeprom_len(netdev);

	if (eeprom->offset > eeprom->offset + eeprom->len)
		return -EINVAL;

	if ((eeprom->offset + eeprom->len) > max_len)
		eeprom->len = (max_len - eeprom->offset);

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kmalloc(max_len, GFP_KERNEL);
	if (!eeprom_buff)
		return -ENOMEM;

	ptr = (void *)eeprom_buff;

	if (eeprom->offset & 1) {


		eeprom_buff[0] = ixgb_read_eeprom(hw, first_word);
		ptr++;
	}
	if ((eeprom->offset + eeprom->len) & 1) {


		eeprom_buff[last_word - first_word]
			= ixgb_read_eeprom(hw, last_word);
	}

	memcpy(ptr, bytes, eeprom->len);
	for (i = 0; i <= (last_word - first_word); i++)
		ixgb_write_eeprom(hw, first_word + i, eeprom_buff[i]);


	if (first_word <= EEPROM_CHECKSUM_REG)
		ixgb_update_eeprom_checksum(hw);

	kfree(eeprom_buff);
	return 0;
}
