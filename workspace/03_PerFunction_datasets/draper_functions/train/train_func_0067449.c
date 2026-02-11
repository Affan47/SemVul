add_lack_common_node(Module_table *mod_sb, Module_table *mod_org)
{
    Common_table *ct;
    Common_table *ct0;

    for (ct = mod_sb->common_head; ct != NULL; ct = ct->next) {
        ct0 = search_common_table(mod_org, ct->region);
        merge_common_table(mod_sb, ct, ct0);
    }
}
