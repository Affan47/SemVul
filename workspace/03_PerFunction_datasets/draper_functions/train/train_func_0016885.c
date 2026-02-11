update_speed() {
    double delta_t = dtime() - start_time;
    if (delta_t > 0) {
        xfer_speed = (bytes_xferred-start_bytes_xferred) / delta_t;
    }
}
