kv_convert_vid7_to_vid2(struct amdgpu_device *adev,
				   struct sumo_vid_mapping_table *vid_mapping_table,
				   u32 vid_7bit)
{
	struct amdgpu_clock_voltage_dependency_table *vddc_sclk_table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	u32 i;

	if (vddc_sclk_table && vddc_sclk_table->count) {
		for (i = 0; i < vddc_sclk_table->count; i++) {
			if (vddc_sclk_table->entries[i].v == vid_7bit)
				return i;
		}
		return vddc_sclk_table->count - 1;
	} else {
		for (i = 0; i < vid_mapping_table->num_entries; i++) {
			if (vid_mapping_table->entries[i].vid_7bit == vid_7bit)
				return vid_mapping_table->entries[i].vid_2bit;
		}

		return vid_mapping_table->entries[vid_mapping_table->num_entries - 1].vid_2bit;
	}
}
