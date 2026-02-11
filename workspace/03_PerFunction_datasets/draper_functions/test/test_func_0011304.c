finishPayload(decodeISF_t * pDecISF, const char * label, INT64 endPayload)
{
    int err = OK;
    unsigned char c;
    int lineNb,
        i,j;


    if (endPayload != pDecISF->bytesRead)
    {
        lineNb = (endPayload + 15 - pDecISF->bytesRead)/16;
        LOG(stdout,"%s: %lld bytes to read\n",
                label,
                endPayload - pDecISF->bytesRead);

        for (i=0; i<lineNb && err == OK; i++)
        {
            LOG(stdout,"%s ",label);
            j = 0;
            do
            {
                err = readByte (pDecISF, &c);
                j++;


                if (err == OK)
                    LOG(stdout,"%.2X ", c);
            } while (err == OK && pDecISF->bytesRead < endPayload && j<16);
            LOG(stdout,"\n");
        }
    }
    return err;
}
