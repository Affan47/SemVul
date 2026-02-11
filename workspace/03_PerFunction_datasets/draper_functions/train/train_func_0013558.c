cpu_coarse(HOST& host){
    if (strcasestr(host.p_vendor, "Intel")) return Intel;
    if (strcasestr(host.p_vendor, "AMD")) return AMD;
    if (strcasestr(host.p_vendor, "Macintosh")) return Macintosh;
    return nocpu;
}
