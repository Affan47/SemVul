z_output_stream (void)
{

    flush_buffer ();

    switch ((short) zargs[0]) {

    case  1: ostream_screen = TRUE;
	     break;
    case -1: ostream_screen = FALSE;
	     break;
    case  2: if (!ostream_script) script_open ();
	     break;
    case -2: if (ostream_script) script_close ();
	     break;
    case  3: memory_open (zargs[1], zargs[2], zargc >= 3);
	     break;
    case -3: memory_close ();
	     break;
    case  4: if (!ostream_record) record_open ();
	     break;
    case -4: if (ostream_record) record_close ();
	     break;

    }

}
