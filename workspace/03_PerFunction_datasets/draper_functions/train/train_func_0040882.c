chatbox_close()
{
	if (!Chatbox_created)
		return;


	Chat_window.destroy();


	if (Chatbox_small_bitmap != -1) {
		bm_release(Chatbox_small_bitmap);
		Chatbox_small_bitmap = -1;
	}

	if (Chatbox_big_bitmap != -1) {
		bm_release(Chatbox_big_bitmap);
		Chatbox_big_bitmap = -1;
	}

	if (Chatbox_mp_bitmap != -1) {
		bm_release(Chatbox_mp_bitmap);
		Chatbox_mp_bitmap = -1;
	}


	chatbox_clear();
	Chatbox_created = 0;
}
