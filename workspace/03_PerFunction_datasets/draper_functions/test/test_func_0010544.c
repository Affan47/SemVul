ompcbe_ddsche_write_setmt(csbe_context *cx, Hmdf_context *hcx, int mt_no)
{
    Func_table *fpt;
    ASSERT_SCHEDULER_MODULE;

    fpt = search_func_table(hcx->hmdf->block->module->entry);
    if (!opt_direct_scheduler) {
	if ((opt_frame || opt_recursive) && opt_c_dynamic_scheduler) {
	    if(fpt->rec_flg) {
            csbe_printf(cx,
                        "%s(/*mtg_id*/%d, /*cl_no*/%d, /*pc_no*/%d, /*mt_no*/%d, %s);\n",
                        SCHE_FUNC_NAME_SETMT,
                        hcx->mtg_id, hcx->cl_no, hcx->pc_no, mt_no,
                        LOCAL_FRAME_POINTER_NAME);
	    } else {
            csbe_printf(cx,
                        "%s(/*mtg_id*/%d, /*cl_no*/%d, /*pc_no*/%d, /*mt_no*/%d, NULL);\n",
                        SCHE_FUNC_NAME_SETMT,
                        hcx->mtg_id, hcx->cl_no, hcx->pc_no, mt_no);
	    }
	}
        else {
            csbe_printf(cx,
                        "%s(/*mtg_id*/%d, /*cl_no*/%d, /*pc_no*/%d, /*mt_no*/%d);\n",
                        SCHE_FUNC_NAME_SETMT,
                        hcx->mtg_id, hcx->cl_no, hcx->pc_no, mt_no);
	}
    } else {
        char name[64];
        ddsche_make_setmt_module_name(name,
                                      hcx->mtg_id,
                                      hcx->cl_no,
                                      hcx->pc_no);
        csbe_printf(cx,
                    "%s = %d;\n",
                    SET_MT_VAR_NAME,
                    mt_no);

	if ((opt_frame || (opt_recursive && fpt->rec_flg)) && opt_c_dynamic_scheduler)
            csbe_printf(cx,
                        "%s(&%s, %s);\n", name,
                        SET_MT_VAR_NAME, LOCAL_FRAME_POINTER_NAME);
        else
            csbe_printf(cx,
                        "%s(&%s);\n", name,
                        SET_MT_VAR_NAME);
    }
}
