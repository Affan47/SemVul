set_loops_formal_lu(Module_table **mod_sb, Block *block, Operand **arg_list)
{
    Block *bpt;

    for (bpt = block; bpt != NULL; bpt = bpt->next) {
        if (block_has_dlg_tag(bpt) || block_has_car_tag(bpt))
            set_loop_formal_lu(arg_list, mod_sb);

        if (bpt->inner != NULL)
            set_loops_formal_lu(mod_sb, bpt->inner, arg_list);
    }
}
