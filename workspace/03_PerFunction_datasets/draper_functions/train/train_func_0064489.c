base_bcol_basesmuma_exchange_ctl_params(
    mca_bcol_basesmuma_module_t *sm_bcol_module,
    mca_bcol_basesmuma_component_t *cs,
    sm_buffer_mgmt *ctl_mgmt, list_data_t *data_blk)
{
    int ret=OMPI_SUCCESS,i,loop_limit;
    int leading_dim, buf_id;
    void *mem_offset;
    unsigned char *base_ptr;
    mca_bcol_basesmuma_ctl_struct_t *ctl_ptr;


    mem_offset = (void *)((uintptr_t)data_blk->data -
                          (uintptr_t)cs->sm_ctl_structs->data_addr);


    loop_limit=cs->basesmuma_num_mem_banks+ctl_mgmt->number_of_buffs;
    leading_dim=ctl_mgmt->size_of_group;
    ret=comm_allgather_pml(&mem_offset, ctl_mgmt->ctl_buffs, sizeof(void *),
                           MPI_BYTE, sm_bcol_module->super.sbgp_partner_module->my_index,
                           sm_bcol_module->super.sbgp_partner_module->group_size,
                           sm_bcol_module->super.sbgp_partner_module->group_list,
                           sm_bcol_module->super.sbgp_partner_module->group_comm);
    if( OMPI_SUCCESS != ret ) {
        goto exit_ERROR;
    }

#if 0
    ret=base_bcol_basesmuma_exchange_offsets( sm_bcol_module,
            (void **)ctl_mgmt->ctl_buffs, mem_offset, loop_limit, leading_dim);
    if( OMPI_SUCCESS != ret ) {
        goto exit_ERROR;
    }
#endif


    for (i=0;i< sm_bcol_module->super.sbgp_partner_module->group_size;i++) {


        int array_id=SM_ARRAY_INDEX(leading_dim,0,i);
        if( i == sm_bcol_module->super.sbgp_partner_module->my_index) {

            base_ptr=cs->sm_ctl_structs->map_addr;
        } else {
            base_ptr=sm_bcol_module->ctl_backing_files_info[i]->sm_mmap->map_addr;
        }
        ctl_mgmt->ctl_buffs[array_id]=(void *)
            (uintptr_t)(((uint64_t)(uintptr_t)ctl_mgmt->ctl_buffs[array_id])+(uint64_t)(uintptr_t)base_ptr);
        for( buf_id = 1 ; buf_id < loop_limit ; buf_id++ ) {
            int array_id_m1=SM_ARRAY_INDEX(leading_dim,(buf_id-1),i);
            array_id=SM_ARRAY_INDEX(leading_dim,buf_id,i);
            ctl_mgmt->ctl_buffs[array_id]=(void *) (uintptr_t)((uint64_t)(uintptr_t)(ctl_mgmt->ctl_buffs[array_id_m1])+
                (uint64_t)(uintptr_t)sizeof(mca_bcol_basesmuma_ctl_struct_t));
        }
    }

    for( buf_id = 0 ; buf_id < loop_limit ; buf_id++ ) {

        int my_idx=sm_bcol_module->super.sbgp_partner_module->my_index;
        int array_id=SM_ARRAY_INDEX(leading_dim,buf_id,my_idx);
        ctl_ptr = (mca_bcol_basesmuma_ctl_struct_t *)
                ctl_mgmt->ctl_buffs[array_id];


        ctl_ptr->sequence_number=-1;
        ctl_ptr->flag=-1;
        ctl_ptr->index=0;
        ctl_ptr->src_ptr = NULL;
    }

    return ret;

exit_ERROR:

    return ret;
}
