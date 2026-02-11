setWatchedEvents(AvahiWatchEvent event)
{
    if (!(event & AVAHI_WATCH_IN)) { delete m_in; m_in=0; }
    if (!(event & AVAHI_WATCH_OUT)) { delete m_out; m_out=0; }
    if (event & AVAHI_WATCH_IN) {
	m_in = new QSocketNotifier(m_fd,QSocketNotifier::Read, this);
	connect(m_in,SIGNAL(activated(int)),SLOT(gotIn()));
    }
    if (event & AVAHI_WATCH_OUT) {
	m_out = new QSocketNotifier(m_fd,QSocketNotifier::Write, this);
	connect(m_out,SIGNAL(activated(int)),SLOT(gotOut()));
    }
}
