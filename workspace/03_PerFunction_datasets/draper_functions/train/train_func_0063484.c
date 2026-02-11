write_barrier_common_type5(fsbe_context *cx,
                           Module_table *module,
                           const char *common_name)
{
    if (get_num_of_barriers(module) > 0)
        ompfbe_iprintf(cx, "COMMON/BARRIER_%s/BARRIER_FLG\n", common_name);
    if (module->red_head != NULL)
	write_sync_reduction_common(cx, module);
}
