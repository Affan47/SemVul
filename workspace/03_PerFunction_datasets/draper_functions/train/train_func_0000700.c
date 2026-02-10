write(
    MIOFILE& out, bool include_net_info, bool include_coprocs
) {
    char pv[265], pm[256], pf[1024], osn[256], osv[256], pn[256];
    out.printf(
        "<host_info>\n"
        "    <timezone>%d</timezone>\n",
        timezone
    );
    if (include_net_info) {
        out.printf(
            "    <domain_name>%s</domain_name>\n"
            "    <ip_addr>%s</ip_addr>\n",
            domain_name,
            ip_addr
        );
    }
    xml_escape(p_vendor, pv, sizeof(pv));
    xml_escape(p_model, pm, sizeof(pm));
    xml_escape(p_features, pf, sizeof(pf));
    xml_escape(os_name, osn, sizeof(osn));
    xml_escape(os_version, osv, sizeof(osv));
    out.printf(
        "    <host_cpid>%s</host_cpid>\n"
        "    <p_ncpus>%d</p_ncpus>\n"
        "    <p_vendor>%s</p_vendor>\n"
        "    <p_model>%s</p_model>\n"
        "    <p_features>%s</p_features>\n"
        "    <p_fpops>%f</p_fpops>\n"
        "    <p_iops>%f</p_iops>\n"
        "    <p_membw>%f</p_membw>\n"
        "    <p_calculated>%f</p_calculated>\n"
        "    <p_vm_extensions_disabled>%d</p_vm_extensions_disabled>\n"
        "    <m_nbytes>%f</m_nbytes>\n"
        "    <m_cache>%f</m_cache>\n"
        "    <m_swap>%f</m_swap>\n"
        "    <d_total>%f</d_total>\n"
        "    <d_free>%f</d_free>\n"
        "    <os_name>%s</os_name>\n"
        "    <os_version>%s</os_version>\n",
        host_cpid,
        p_ncpus,
        pv,
        pm,
        pf,
        p_fpops,
        p_iops,
        p_membw,
        p_calculated,
        p_vm_extensions_disabled?1:0,
        m_nbytes,
        m_cache,
        m_swap,
        d_total,
        d_free,
        osn,
        osv
    );
    if (strlen(product_name)) {
        xml_escape(product_name, pn, sizeof(pn));
        out.printf(
            "    <product_name>%s</product_name>\n",
            pn
        );
    }
    if (strlen(mac_address)) {
        out.printf(
            "    <mac_address>%s</mac_address>\n",
            mac_address
        );
    }
    if (strlen(virtualbox_version)) {
        char buf[256];
        xml_escape(virtualbox_version, buf, sizeof(buf));
        out.printf(
            "    <virtualbox_version>%s</virtualbox_version>\n",
            buf
        );
    }
    if (include_coprocs) {
        this->coprocs.write_xml(out, false);
    }


    for (int i=0; i<num_cpu_opencl_platforms; i++) {
        cpu_opencl_prop[i].write_xml(out);
    }
    out.printf(
        "</host_info>\n"
    );
    return 0;
}
