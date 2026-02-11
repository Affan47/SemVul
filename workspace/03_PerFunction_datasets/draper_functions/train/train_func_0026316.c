write(MIOFILE& out) {
    unsigned int i;

    out.printf(
        "<workunit>\n"
        "    <name>%s</name>\n"
        "    <app_name>%s</app_name>\n"
        "    <version_num>%d</version_num>\n"

        "    <rsc_fpops_est>%f</rsc_fpops_est>\n"
        "    <rsc_fpops_bound>%f</rsc_fpops_bound>\n"
        "    <rsc_memory_bound>%f</rsc_memory_bound>\n"
        "    <rsc_disk_bound>%f</rsc_disk_bound>\n",
        name,
        app_name,
        version_num,

        rsc_fpops_est,
        rsc_fpops_bound,
        rsc_memory_bound,
        rsc_disk_bound
    );
    if (command_line.size()) {
        out.printf(
            "    <command_line>\n"
            "%s\n"
            "    </command_line>\n",
            command_line.c_str()
        );
    }
    for (i=0; i<input_files.size(); i++) {
        input_files[i].write(out);
    }
    out.printf("</workunit>\n");
    return 0;
}
