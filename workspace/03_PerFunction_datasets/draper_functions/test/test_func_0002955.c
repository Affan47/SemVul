socket_strerror(int err) {
    if (err <= 0) return io_strerror(err);
    switch (err) {
        case EADDRINUSE: return "address already in use";
        case EISCONN: return "already connected";
        case EACCES: return "permission denied";
        case ECONNREFUSED: return "connection refused";
        case ECONNABORTED: return "closed";
        case ECONNRESET: return "closed";
        case ETIMEDOUT: return "timeout";
        default: return strerror(err);
    }
}
