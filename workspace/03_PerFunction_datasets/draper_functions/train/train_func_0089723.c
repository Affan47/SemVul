detach_all_ostreams(dbg::level lvl)
{
    out(debug) << prefix(debug) << "dbg::detach_all_ostreams("
               << LEVEL_NAMES[lvl]
               << ")\n";

    source_map[""].clear_ostream(lvl);
}
