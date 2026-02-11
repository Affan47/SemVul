wildcarded_ip_found(Octstr *ip, Octstr *needle, Octstr *ip_sep)
{
    List *ip_fragments,
         *needle_fragments;
    long i;
    Octstr *ip_fragment,
           *needle_fragment;

    ip_fragments = octstr_split(ip, ip_sep);
    needle_fragments = octstr_split(needle, ip_sep);

    gw_assert(gwlist_len(ip_fragments) == gwlist_len(needle_fragments));
    for (i = 0; i < gwlist_len(ip_fragments); ++i) {
        ip_fragment = gwlist_get(ip_fragments, i);
        needle_fragment = gwlist_get(needle_fragments, i);
        if (octstr_compare(ip_fragment, needle_fragment) != 0 &&
                octstr_compare(ip_fragment, octstr_imm("*")) != 0)
 	        goto not_found;
    }

    gwlist_destroy(ip_fragments, octstr_destroy_item);
    gwlist_destroy(needle_fragments, octstr_destroy_item);
    return 1;

not_found:
    gwlist_destroy(ip_fragments, octstr_destroy_item);
    gwlist_destroy(needle_fragments, octstr_destroy_item);
    return 0;
}
