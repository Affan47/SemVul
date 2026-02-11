pine_rfc822_output(METAENV *header, struct mail_bodystruct *body, soutr_t f, void *s)
{
    int we_cancel = 0;
    long retval;

    dprint((4, "-- pine_rfc822_output\n"));

    we_cancel = busy_cue(NULL, NULL, 1);
    pine_encode_body(body);

    retval = pine_rfc822_header(header, body, f, s)
	   && (body ? pine_rfc822_output_body(body, f, s) : 1L);

    if(we_cancel)
      cancel_busy_cue(-1);

    return(retval);
}
