set_new_hmdf_tree( Module_table *module_head,
		   Module_hmdf_information *module_hmdf_info_list )
{
    Module_table            **ma;
    int                     nma, i;
    int                     total_pe_num;
    Module_hmdf_information *module_hmdf_info;

    ma = get_sorted_module_array( module_head, &nma );

    initialize_all_hmdf_table( module_head );

    if( !inline_by_hmdf_info_fg ){
        for( i=0; i < nma; i++ ){
            if( ma[i]->kind != MODULE_BLOCKDATA ){


		    add_new_hmdf( ma[i], module_hmdf_info_list );

		    remaking_hmdf_tree( ma[i]->block_head, ma[i]->super_hmdf );

            }
        }

#ifdef LAYER_INFORMATION
        if( info_fp != NULL )
            print_layer_info( info_fp, module_head, module_hmdf_info_list );
#endif

    }else{
        for( i=0; i < nma; i++ ){
            total_pe_num = module_head->super_hmdf->pe_num;
            inlining_by_hmdf_info( ma[i], module_hmdf_info_list, total_pe_num );

        }

#ifdef LAYER_INFORMATION
        if( info_fp != NULL )
            print_layer_info( info_fp, module_head, module_hmdf_info_list );
#endif

        module_hmdf_info = find_module_hmdf_info( module_head, module_hmdf_info_list );

        sb_extension_for_inlining( module_head,
                                   module_hmdf_info->inline_info_list,
                                   module_hmdf_info_list );

    }

    free( ma );
}
