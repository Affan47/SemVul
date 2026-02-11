iwl_mvm_tt_temp_changed(struct iwl_mvm *mvm, u32 temp)
{

	if (mvm->temperature_test)
		return;

	if (mvm->temperature == temp)
		return;

	mvm->temperature = temp;
	iwl_mvm_tt_handler(mvm);
}
