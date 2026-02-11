send_event_process_exited(OutputStream * out, ChildProcess * prs) {
    write_stringz(out, "E");
    write_stringz(out, PROCESSES);
    write_stringz(out, "exited");

    json_write_string(out, pid2id(prs->pid, 0));
    write_stream(out, 0);

    json_write_long(out, prs->exit_code);
    write_stream(out, 0);

    write_stream(out, MARKER_EOM);
}
