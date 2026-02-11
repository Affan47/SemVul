e1000_init_function_pointers_82540(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_init_function_pointers_82540");

	hw->mac.ops.init_params = e1000_init_mac_params_82540;
	hw->nvm.ops.init_params = e1000_init_nvm_params_82540;
	hw->phy.ops.init_params = e1000_init_phy_params_82540;
}
