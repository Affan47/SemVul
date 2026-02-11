get_daily_xfer_history(DAILY_XFER_HISTORY& dxh) {
    SET_LOCALE sl;
    RPC rpc(this);
    int retval;

    retval = rpc.do_rpc("<get_daily_xfer_history/>\n");
    if (retval) return retval;
    return dxh.parse(rpc.xp);
}
