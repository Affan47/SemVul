get_meta_entry(VMG0_) const
{
    uint meta_idx;


    meta_idx = get_meta_idx();


    if (meta_idx < G_meta_table->get_count())
        return G_meta_table->get_entry(meta_idx);
    else
        return 0;
}
