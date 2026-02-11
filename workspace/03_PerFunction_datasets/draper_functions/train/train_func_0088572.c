return_to_main_buffer() {

    while(buffer_count) {
	zzpop_buffer_state();
	--buffer_count;
    }
    command_buffer_count = 0;
    BEGIN(INITIAL);
}
