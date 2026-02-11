write_queued_chars() {
    if (tqhead != tqtail) {
        if (typing_delay_ms && delay_ms)
            write_tqchar();
        else
            write_all_qchars();
    }
}
