send_event_context_added(OutputStream * out, BreakpointInfo * bp) {
    write_stringz(out, "E");
    write_stringz(out, BREAKPOINTS);
    write_stringz(out, "contextAdded");

    write_stream(out, '[');
    write_breakpoint_properties(out, bp);
    write_stream(out, ']');
    write_stream(out, 0);
    write_stream(out, MARKER_EOM);
}
