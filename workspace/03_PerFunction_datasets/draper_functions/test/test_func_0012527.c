multi_passwd_do(char *passwd)
{
	int k;

	while(Multi_passwd_done == -1){

		game_set_frametime(-1);
		game_do_state_common(gameseq_get_state());

		k = Multi_pwd_window.process();


		switch(k){
		case KEY_ESC :

			Multi_passwd_done = 0;
			break;
		}


		if(Multi_pwd_passwd.changed()){
			strcpy(passwd,"");
			Multi_pwd_passwd.get_text(passwd);
		}


		multi_passwd_process_buttons();


		gr_reset_clip();
		gr_clear();
		if(Multi_passwd_background >= 0){
			gr_restore_screen(Multi_passwd_background);
		}
		gr_set_bitmap(Multi_pwd_bitmap);
		gr_bitmap(0,0);
		Multi_pwd_window.draw();


		gr_flip();
	}
}
