ompfbe_write_sync_init_com(fsbe_context *cx, Module_table *module)
{
    int common_size = get_sync_size(module);

    if(common_size > 0){
	int cl;
	int pc;
	char *module_name = module->name;
	char common_name[256];

	if(!strcmp(module_name,"*MAIN*")){
	    module_name = "MAIN";
	}

        for (cl = 0; cl < module->super_hmdf->clustering_num; cl++) {
            for (pc = 0; pc < module->super_hmdf->pc_num; pc++) {
                sprintf(common_name, "COM_SYNC_%s_CL%d_PC%d",
                        module_name, cl, pc);

                ompfbe_iprintf(cx, "COMMON /%s/DUMMY_CL%d_PC%d_%s\n",
                               common_name, cl, pc,module_name);
                if (!opt_no_common_save)
		  ompfbe_iprintf(cx, "SAVE /%s/\n", common_name);
	    }
	}
    }
}
