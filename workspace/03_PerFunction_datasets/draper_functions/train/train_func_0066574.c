handle_news (NetLinkPidScanner *nls, struct cn_msg *cn_hdr)
{
	struct proc_event *ev;

        ev = (struct proc_event*)cn_hdr->data;

        switch (ev->what) {
        case PROC_EVENT_FORK:

		if (ev->event_data.fork.child_pid == ev->event_data.fork.child_tgid)
			pid_scanner_emit_paternity ((PidScanner *)nls,
						    ev->event_data.fork.child_tgid,
						    ev->event_data.fork.parent_tgid);

        case PROC_EVENT_EXIT:
		pthread_mutex_lock (&nls->lock);
		nls->buffer = realloc (nls->buffer, sizeof (struct proc_event) * (nls->buffer_size + 1));
		memcpy (&(nls->buffer[nls->buffer_size]), ev, sizeof (struct proc_event));
		nls->buffer_size++;
		pthread_mutex_unlock (&nls->lock);
		break;

        case PROC_EVENT_EXEC:
		pid_scanner_emit_exec ((PidScanner *)nls, ev->event_data.exec.process_pid);
		break;
        case PROC_EVENT_UID:
        default:
                break;
        }
}
