stream_word (const zchar *s)
{

    if (ostream_memory && !message)

	memory_word (s);

    else {

	if (ostream_screen)
	    screen_word (s);
	if (ostream_script && enable_scripting)
	    script_word (s);

    }

}
