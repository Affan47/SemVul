igb_init_nvm_params_i210(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	struct e1000_nvm_info *nvm = &hw->nvm;

	nvm->ops.acquire = igb_acquire_nvm_i210;
	nvm->ops.release = igb_release_nvm_i210;
	nvm->ops.valid_led_default = igb_valid_led_default_i210;


	if (igb_get_flash_presence_i210(hw)) {
		hw->nvm.type = e1000_nvm_flash_hw;
		nvm->ops.read    = igb_read_nvm_srrd_i210;
		nvm->ops.write   = igb_write_nvm_srwr_i210;
		nvm->ops.validate = igb_validate_nvm_checksum_i210;
		nvm->ops.update   = igb_update_nvm_checksum_i210;
	} else {
		hw->nvm.type = e1000_nvm_invm;
		nvm->ops.read     = igb_read_invm_i210;
		nvm->ops.write    = NULL;
		nvm->ops.validate = NULL;
		nvm->ops.update   = NULL;
	}
	return ret_val;
}
