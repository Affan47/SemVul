multi_voice_test_process()
{

	if(Multi_voice_test_record_stamp == -1){
		return;
	}


	if(timestamp_elapsed(Multi_voice_test_record_stamp)){
		Multi_voice_test_record_stamp = -1;
		Multi_voice_test_packet_tossed = 0;
	}
}
