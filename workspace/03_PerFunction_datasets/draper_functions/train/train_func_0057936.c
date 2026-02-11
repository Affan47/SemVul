mimeview_check_sig_worker_thread(void *data)
{
	MimeView *mimeview = (MimeView *)data;
	MimeInfo *mimeinfo = mimeview->siginfo;

	debug_print("checking...\n");

	if (!mimeview->check_data)
		return NULL;

	if (mimeinfo && mimeinfo == mimeview->check_data->siginfo) {
		privacy_mimeinfo_check_signature(mimeinfo);
		if (mimeview->check_data && mimeview->check_data->cancel_th_init) {
			mimeview->check_data->cancel_th_init = FALSE;
			pthread_cancel(mimeview->check_data->cancel_th);
		}
	} else {


		g_warning("different siginfo!\n");
		mimeview_check_data_reset(mimeview);
		return NULL;
	}


	g_timeout_add(0,mimeview_check_sig_thread_cb,mimeview);

	return NULL;
}
