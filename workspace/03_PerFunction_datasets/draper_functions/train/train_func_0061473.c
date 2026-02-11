q_watch_new(const AvahiPoll *api, int fd, AvahiWatchEvent event, AvahiWatchCallback callback,
    void *userdata)
{
    return new AvahiWatch(fd, event, callback, userdata);
}
