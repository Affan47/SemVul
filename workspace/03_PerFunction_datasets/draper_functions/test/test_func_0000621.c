e1000_set_eeprom(struct net_device *netdev,
			    struct ethtool_eeprom *eeprom, u8 *bytes)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	void *ptr;
	int max_len;
	int first_word;
	int last_word;
	int ret_val = 0;
	u16 i;

	if (eeprom->len == 0)
		return -EOPNOTSUPP;

	if (eeprom->magic !=
	    (adapter->pdev->vendor | (adapter->pdev->device << 16)))
		return -EFAULT;

	if (adapter->flags & FLAG_READ_ONLY_NVM)
		return -EINVAL;

	max_len = hw->nvm.word_size * 2;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kmalloc(max_len, GFP_KERNEL);
	if (!eeprom_buff)
		return -ENOMEM;

	ptr = (void *)eeprom_buff;

	pm_runtime_get_sync(netdev->dev.parent);

	if (eeprom->offset & 1) {


		ret_val = e1000_read_nvm(hw, first_word, 1, &eeprom_buff[0]);
		ptr++;
	}
	if (((eeprom->offset + eeprom->len) & 1) && (!ret_val))


		ret_val = e1000_read_nvm(hw, last_word, 1,
					 &eeprom_buff[last_word - first_word]);

	if (ret_val)
		goto out;


	for (i = 0; i < last_word - first_word + 1; i++)
		le16_to_cpus(&eeprom_buff[i]);

	memcpy(ptr, bytes, eeprom->len);

	for (i = 0; i < last_word - first_word + 1; i++)
		cpu_to_le16s(&eeprom_buff[i]);

	ret_val = e1000_write_nvm(hw, first_word,
				  last_word - first_word + 1, eeprom_buff);

	if (ret_val)
		goto out;


	if ((first_word <= NVM_CHECKSUM_REG) ||
	    (hw->mac.type == e1000_82583) ||
	    (hw->mac.type == e1000_82574) ||
	    (hw->mac.type == e1000_82573))
		ret_val = e1000e_update_nvm_checksum(hw);

out:
	pm_runtime_put_sync(netdev->dev.parent);
	kfree(eeprom_buff);
	return ret_val;
}
