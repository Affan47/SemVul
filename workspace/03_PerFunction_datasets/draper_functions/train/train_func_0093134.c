save_addr_list_cb(struct ntb_main_context_source *source,
                  void *user_data)
{
        struct ntb_network *nw = user_data;
        struct ntb_buffer buffer;
        struct ntb_network_addr *addr;
        struct ntb_store_addr *store_addr;
        int n_addrs = 0;
        int64_t now = ntb_main_context_get_wall_clock(NULL);
        int64_t age;

        ntb_buffer_init(&buffer);

        ntb_list_for_each(addr, &nw->addrs, link) {
                age = now - addr->advertise_time;

                if (age > NTB_NETWORK_MAX_ADDR_AGE)
                        continue;

                ntb_buffer_ensure_size(&buffer,
                                       buffer.length + sizeof *store_addr);
                store_addr =
                        (struct ntb_store_addr *) (buffer.data + buffer.length);
                store_addr->timestamp = addr->advertise_time;
                store_addr->stream = addr->stream;
                store_addr->services = addr->services;
                store_addr->address = addr->address;
                buffer.length += sizeof *store_addr;
                n_addrs++;
        }


        ntb_store_save_addr_list(NULL,
                                 (struct ntb_store_addr *) buffer.data,
                                 n_addrs);

        ntb_main_context_remove_source(source);
        nw->save_addr_list_source = NULL;
}
