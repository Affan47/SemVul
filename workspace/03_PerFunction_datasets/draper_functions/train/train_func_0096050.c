drv_PHAnderson_quit(const int quiet)
{

    info("%s: shutting down.", Name);

    drv_generic_text_quit();

    drv_PHAnderson_clear();


    if (!quiet) {
	drv_generic_text_greet("goodbye!", NULL);
    }

    debug("closing connection");
    drv_PHAnderson_close();

    return (0);
}
