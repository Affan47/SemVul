vg_mda_used_count(const struct volume_group *vg)
{
       uint32_t used_count = 0;
       struct metadata_area *mda;


       dm_list_iterate_items(mda, &vg->fid->metadata_areas_in_use)
	       if (!mda_is_ignored(mda))
		       used_count++;

       return used_count;
}
