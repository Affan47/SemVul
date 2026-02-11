ompcbe_write_frame(csbe_context *cx, Module_table *module)
{
    int pc_no;
    int cl_no;
    Func_table *fpt;
    fpt = search_func_table(module->entry);

    if (!hmdf_pc_and_clustering_number(module->super_hmdf,
                                       get_current_pe_number(),
                                       &pc_no,
                                       &cl_no)) {
        fatal("umumu\n");
    }

    if (opt_include_mpcore_goods
        && (module->entry == 0 || opt_add_set_pe_to_all)) {
        csbe_printf(cx, "set_pe(%d);\n", get_current_pe_number());
    }

    if (opt_frame || (fpt != NULL && fpt->rec_flg)) {
	csbe_printf(cx, "Frame *frame = oscar_get_frame(%d,%d,%d);\n",
		    module->entry, cl_no, pc_no);
        csbe_printf(cx, "struct %s%d *%s = oscar_frame_local(frame);\n",
                    LOCAL_FRAME_STRUCT_NAME,
                    module->entry,
                    LOCAL_FRAME_POINTER_NAME);
    }
}
