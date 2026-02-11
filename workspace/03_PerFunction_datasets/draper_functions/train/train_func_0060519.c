match_modex(ompi_btl_usnic_module_t *module,
                       ompi_btl_usnic_proc_t *proc)
{
    size_t i;


    for (i = 0; i < proc->proc_modex_count; ++i) {
        if (!proc->proc_modex_claimed[i]) {
            char my_ip_string[32], peer_ip_string[32];
            uint32_t mynet, peernet;

            inet_ntop(AF_INET, &module->if_ipv4_addr,
                      my_ip_string, sizeof(my_ip_string));
            inet_ntop(AF_INET, &proc->proc_modex[i].ipv4_addr,
                      peer_ip_string, sizeof(peer_ip_string));
            opal_output_verbose(5, USNIC_OUT,
                                "btl:usnic:match_modex: checking my IP address/subnet (%s/%d) vs. peer (%s/%d)",
                                my_ip_string, module->if_cidrmask,
                                peer_ip_string, proc->proc_modex[i].cidrmask);


            mynet   = ompi_btl_usnic_get_ipv4_subnet(module->if_ipv4_addr,
                                                     module->if_cidrmask);
            peernet = ompi_btl_usnic_get_ipv4_subnet(proc->proc_modex[i].ipv4_addr,
                                                     proc->proc_modex[i].cidrmask);


            if (mynet == peernet) {
                opal_output_verbose(5, USNIC_OUT, "btl:usnic:match_modex: IP networks match -- yay!");
                break;
            }
            else {
                opal_output_verbose(5, USNIC_OUT, "btl:usnic:match_modex: IP networks DO NOT match -- mynet=%#x peernet=%#x",
                                    mynet, peernet);
            }
        }
    }


    if (i >= proc->proc_modex_count) {
        return -1;
    }


    if (proc->proc_modex[i].mtu != module->if_mtu) {
        opal_show_help("help-mpi-btl-usnic.txt", "MTU mismatch",
                       true,
                       ompi_process_info.nodename,
                       ibv_get_device_name(module->device),
                       module->port_num,
                       module->if_mtu,
                       (NULL == proc->proc_ompi->proc_hostname) ?
                       "unknown" : proc->proc_ompi->proc_hostname,
                       proc->proc_modex[i].mtu);
        return -1;
    }

    return i;
}
