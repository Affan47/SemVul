isInactive() {
    return isIdle() && (elapsed - last_action) > 10.0;
}
