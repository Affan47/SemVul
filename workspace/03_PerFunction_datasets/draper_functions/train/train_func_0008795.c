stopped_cleanup()
{


	if (this->running_ || !this->stopped_cleanup_needed())
		return;


	unset_stop_timeouts();


	if (WIFEXITED(waitpid_status_)) {
		int exit_status = WEXITSTATUS(waitpid_status_);

		if (exit_status != 0) {

			std::string msg = (translator_func_ ? translator_func_(exit_status, translator_func_data_)
					: "[no translator function, exit code: " + hz::number_to_string(exit_status));
			push_error(Error<int>("exit", ErrorLevel::warn, exit_status, msg), false);
		}

	} else {
		if (WIFSIGNALED(waitpid_status_)) {
			int sig_num = WTERMSIG(waitpid_status_);


			if (sig_num != this->kill_signal_sent_) {
				push_error(Error<int>("signal", ErrorLevel::error, sig_num), false);
			} else {
				push_error(Error<int>("signal", ErrorLevel::warn, sig_num), false);
			}
		}
	}

	g_spawn_close_pid(this->pid_);

	cleanup_members();

	this->running_ = false;
}
