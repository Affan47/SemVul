mca_btl_tcp_component_exchange(void)
{
     int rc = 0, index;
     size_t i = 0;
     size_t size = mca_btl_tcp_component.tcp_addr_count *
                   mca_btl_tcp_component.tcp_num_links * sizeof(mca_btl_tcp_addr_t);


     size_t xfer_size = 0;
     size_t current_addr = 0;

     if(mca_btl_tcp_component.tcp_num_btls != 0) {
         mca_btl_tcp_addr_t *addrs = (mca_btl_tcp_addr_t *)malloc(size);
         memset(addrs, 0, size);


         for( i = 0; i < mca_btl_tcp_component.tcp_num_btls; i++ ) {
             for (index = opal_ifbegin(); index >= 0;
                     index = opal_ifnext(index)) {
                 struct sockaddr_storage my_ss;


                 if (opal_ifindextokindex (index) !=
                         mca_btl_tcp_component.tcp_btls[i]->tcp_ifkindex) {
                     continue;
                 }

                 if (OPAL_SUCCESS !=
                     opal_ifindextoaddr(index, (struct sockaddr*) &my_ss,
                                        sizeof (my_ss))) {
                     opal_output (0,
                             "btl_tcp_component: problems getting address for index %i (kernel index %i)\n",
                             index, opal_ifindextokindex (index));
                     continue;
                 }

                 if ((AF_INET == my_ss.ss_family) &&
                     (4 != mca_btl_tcp_component.tcp_disable_family)) {
                     memcpy(&addrs[current_addr].addr_inet,
                             &((struct sockaddr_in*)&my_ss)->sin_addr,
                             sizeof(addrs[0].addr_inet));
                     addrs[current_addr].addr_port =
                         mca_btl_tcp_component.tcp_listen_port;
                     addrs[current_addr].addr_family = MCA_BTL_TCP_AF_INET;
                     xfer_size += sizeof (mca_btl_tcp_addr_t);
                     addrs[current_addr].addr_inuse   = 0;
                     addrs[current_addr].addr_ifkindex =
                         opal_ifindextokindex (index);
                     current_addr++;
                 }
#if OPAL_ENABLE_IPV6
                 if ((AF_INET6 == my_ss.ss_family) &&
                     (6 != mca_btl_tcp_component.tcp_disable_family)) {
                     memcpy(&addrs[current_addr].addr_inet,
                             &((struct sockaddr_in6*)&my_ss)->sin6_addr,
                             sizeof(addrs[0].addr_inet));
                     addrs[current_addr].addr_port =
                         mca_btl_tcp_component.tcp6_listen_port;
                     addrs[current_addr].addr_family = MCA_BTL_TCP_AF_INET6;
                     xfer_size += sizeof (mca_btl_tcp_addr_t);
                     addrs[current_addr].addr_inuse   = 0;
                     addrs[current_addr].addr_ifkindex =
                         opal_ifindextokindex (index);
                     current_addr++;
                 }
#endif
             }
         }
         rc =  ompi_modex_send(&mca_btl_tcp_component.super.btl_version,
                               addrs, xfer_size);
         free(addrs);
     }
     return rc;
}
