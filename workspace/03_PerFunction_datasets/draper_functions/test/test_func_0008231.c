EnvisatFile_SetDatasetInfo( EnvisatFile *self,
                                int ds_index,
                                int ds_offset,
                                int ds_size,
                                int num_dsr,
                                int dsr_size )

{
    if( ds_index < 0 || ds_index >= self->ds_count )
        return FAILURE;

    self->ds_info[ds_index]->ds_offset = ds_offset;
    self->ds_info[ds_index]->ds_size = ds_size;
    self->ds_info[ds_index]->num_dsr = num_dsr;
    self->ds_info[ds_index]->dsr_size = dsr_size;
    self->header_dirty = 1;

    return SUCCESS;
}
