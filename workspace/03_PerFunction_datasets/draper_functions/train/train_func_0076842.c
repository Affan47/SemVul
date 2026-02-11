run_benchmarks() {
    int retval;
    SET_LOCALE sl;
    RPC rpc(this);

    retval = rpc.do_rpc("<run_benchmarks/>\n");
    if (retval) return retval;
    return rpc.parse_reply();
}
