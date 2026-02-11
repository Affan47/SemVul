vm_register_metaclasses()
{
    uint i;
    vm_meta_reg_t *entry;


    for (i = 0, entry = G_meta_reg_table ; entry->meta != 0 ;
         ++i, ++entry)
    {


        (*entry->meta)->set_metaclass_reg_index(i);
    }
}
