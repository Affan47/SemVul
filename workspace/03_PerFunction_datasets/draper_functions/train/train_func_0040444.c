readyRead(s8 *buf, u32 len)
{
	signalfd_siginfo *si = (signalfd_siginfo*)buf;
	for (len /= sizeof(*si); len--; si++) {
		FbTerm::instance()->processSignal(si->ssi_signo);
	}
}
