estimate_duration(WORKUNIT& wu, BEST_APP_VERSION& bav) {
    double edu = estimate_duration_unscaled(wu, bav);
    double ed = edu/g_wreq->running_frac;
    if (config.debug_send) {
        log_messages.printf(MSG_NORMAL,
            "[send] est. duration for WU %d: unscaled %.2f scaled %.2f\n",
            wu.id, edu, ed
        );
    }
    return ed;
}
