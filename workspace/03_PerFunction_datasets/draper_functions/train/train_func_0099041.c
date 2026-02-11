igb_get_hw_semaphore_i210(struct e1000_hw *hw)
{
	u32 swsm;
	s32 timeout = hw->nvm.word_size + 1;
	s32 i = 0;


	while (i < timeout) {
		swsm = rd32(E1000_SWSM);
		if (!(swsm & E1000_SWSM_SMBI))
			break;

		udelay(50);
		i++;
	}

	if (i == timeout) {


		if (hw->dev_spec._82575.clear_semaphore_once) {
			hw->dev_spec._82575.clear_semaphore_once = false;
			igb_put_hw_semaphore(hw);
			for (i = 0; i < timeout; i++) {
				swsm = rd32(E1000_SWSM);
				if (!(swsm & E1000_SWSM_SMBI))
					break;

				udelay(50);
			}
		}


		if (i == timeout) {
			hw_dbg("Driver can't access device - SMBI bit is set.\n");
			return -E1000_ERR_NVM;
		}
	}


	for (i = 0; i < timeout; i++) {
		swsm = rd32(E1000_SWSM);
		wr32(E1000_SWSM, swsm | E1000_SWSM_SWESMBI);


		if (rd32(E1000_SWSM) & E1000_SWSM_SWESMBI)
			break;

		udelay(50);
	}

	if (i == timeout) {

		igb_put_hw_semaphore(hw);
		hw_dbg("Driver can't access the NVM\n");
		return -E1000_ERR_NVM;
	}

	return 0;
}
