get_module_entry_from_state_data_number(int state_data_number)
{
    if (state_data_number >= total_state_data_number) {
	ERROR_HENTRY(state_data_number);
    }
    if (state_data_number == -1) {
	return -1;
    }
    return state_data[state_data_number].hmdf_info->block->module->entry;
}
