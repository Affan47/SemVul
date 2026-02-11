message_kill_playing( int message_num )
{
	Assert( message_num < Num_messages_playing );


	if ( Playing_messages[message_num].play_anim) {
		Playing_messages[message_num].play_anim = false;
	}

	if ( (Playing_messages[message_num].wave != -1 ) && snd_is_playing(Playing_messages[message_num].wave) )
		snd_stop( Playing_messages[message_num].wave );

	Playing_messages[message_num].shipnum = -1;

	fsspeech_stop();
}
