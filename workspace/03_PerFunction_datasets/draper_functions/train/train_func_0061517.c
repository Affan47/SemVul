flush_buffer (void)
{


    if (locked || bufpos == 0)
	return;


    buffer[bufpos] = 0;


    locked = TRUE;

    stream_word (buffer);

#ifdef SPEECH_OUTPUT
    os_speech_output(buffer);
#endif

    locked = FALSE;


    bufpos = 0;
    prev_c = 0;

}
