wait_record_exit(GPid pid, int)
{
	DLOG("\n");
	record_pid = -1;

	if (is_recording) {
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &GMplayer::on_delay_record_reboot), 2000);
		return;
	}
}
