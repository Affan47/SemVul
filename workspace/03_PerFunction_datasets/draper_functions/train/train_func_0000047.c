mpicbe_task_write_mf_branch_modules_call(csbe_context *cx, List *list)
{
    List *li;
    Hmdf_table *hmdf;

    csbe_printf(cx, "void %s(int mtg_id, int cl_no, int mt_no, int LAST_BRANCH)\n",
		SCHE_FUNC_NAME_MFBS);
    csbe_printf(cx, "{\n");

    for (li = list; li != NULL; li = li->next) {
        hmdf = li->data;

        if (!hmdf->belong_control_flow) {
            csbe_printf(cx, "if(mtg_id==%d){\n", hmdf->mtg_id);
            mpicbe_task_write_mf_branch_modules_call_body(cx, hmdf);
            csbe_printf(cx, "}\n");
        }
    }

    csbe_printf(cx, "}\n");
}
