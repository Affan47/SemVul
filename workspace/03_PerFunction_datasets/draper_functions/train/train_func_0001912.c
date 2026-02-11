event_modify(const int fd, const int read, const int write, const int active)
{
    int i;
    for (i = 0; i < event_count; i++) {
	if (events[i].fd == fd) {
	    events[i].read = read;
	    events[i].write = write;
	    events[i].active = active;
	    break;
	}
    }
    event_count--;
    events = realloc(events, sizeof(event_t) * event_count);
    return 0;
}
