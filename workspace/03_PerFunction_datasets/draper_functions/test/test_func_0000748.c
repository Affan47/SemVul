netsnmp_access_ipaddress_ioctl_get_interface_count(int sd, struct ifconf * ifc)
{
    int lastlen = 0, i;
    struct ifconf ifc_tmp;

    if (NULL == ifc) {
        memset(&ifc_tmp, 0x0, sizeof(ifc_tmp));
        ifc = &ifc_tmp;
    }


    for (i = 8;; i *= 2) {
        ifc->ifc_buf = (caddr_t)calloc(i, sizeof(struct ifreq));
        if (NULL == ifc->ifc_buf) {
            snmp_log(LOG_ERR, "could not allocate memory for %d interfaces\n",
                     i);
            return -1;
        }
        ifc->ifc_len = i * sizeof(struct ifreq);

        if (ioctl(sd, SIOCGIFCONF, (char *) ifc) < 0) {
            if (errno != EINVAL || lastlen != 0) {


                snmp_log(LOG_ERR, "bad rc from ioctl, errno %d", errno);
                SNMP_FREE(ifc->ifc_buf);
                return -1;
            }


        } else {
            if (ifc->ifc_len == lastlen) {


                break;
            }
            lastlen = ifc->ifc_len;
        }
        free(ifc->ifc_buf);
    }

    if (ifc == &ifc_tmp)
        free(ifc_tmp.ifc_buf);

    return ifc->ifc_len / sizeof(struct ifreq);
}
