us_osc_dispatch_add_entry_with_notify( us_osc_dispatch_t *self,
                                            const char *address_prefix,
                                            const us_osc_dispatch_table_t *dispatch_table,
                                            const us_osc_dispatch_index_t *index_offset,
                                            us_osc_dispatch_notify_proc_t notify_proc )
{
    bool r = false;
    if ( self->map.num_entries < self->map.max_entries )
    {
        char resultant_address[256];
        int item = self->map.num_entries;
        us_osc_dispatch_map_entry_t *entry = &self->map.entries[item];
        r = true;
        entry->table_entry = dispatch_table;
        us_osc_dispatch_index_add( &entry->final_index, index_offset, &dispatch_table->index );
        strcpy( resultant_address, address_prefix );
        strcat( resultant_address, dispatch_table->address );


        if ( !notify_proc )
        {
            notify_proc = self->notify;
        }
        if ( !notify_proc || notify_proc( self, resultant_address, dispatch_table, &entry->final_index ) == true )
        {
            us_trie_add( &self->trie->m_base,
                         (us_trie_node_value_t *)resultant_address,
                         strlen( resultant_address ),
                         (us_trie_node_flags_t)item );
            self->map.num_entries++;
            if ( self->trie->m_base.m_num_nodes >= self->trie->m_base.m_max_nodes )
            {
                r = false;
            }
        }
    }
    return r;
}
