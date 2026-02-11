sumo_convert_voltage_index_to_value(struct radeon_device *rdev,
					       u32 vid_2bit)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	u32 vid_7bit = sumo_convert_vid2_to_vid7(rdev, &pi->sys_info.vid_mapping_table, vid_2bit);

	if (vid_7bit > 0x7C)
		return 0;

	return (15500 - vid_7bit * 125 + 5) / 10;
}
