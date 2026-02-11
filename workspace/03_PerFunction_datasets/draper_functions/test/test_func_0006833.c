getstring(char *prompt, char *buf, int bufl)
{
    char  *result;
    int    savemoremode;
    int    retval;


    savemoremode = setmore(0);
    if (prompt != 0)
    {

        outformat(prompt);


        out_logfile_print(prompt, FALSE);
    }
    outflushn(0);
    outreset();


    if (scrfp != 0)
    {
        int quiet = scrquiet;


        if ((result = qasgets(buf, bufl)) == 0)
        {


            if (quiet && prompt != 0)
                outformat(prompt);
            outflushn(0);
            outreset();


            savemoremode = 1;


            os_nonstop_mode(FALSE);
        }


        retval = 0;
    }


    if (scrfp == 0)
    {

        runstat();


        result = (char *)os_gets((uchar *)buf, bufl);


        retval = (result == 0);
    }


    setmore(savemoremode);


    if (retval != 0)
    {

        return retval;
    }
    else
    {
        char *p;


        out_logfile_print(buf, TRUE);
        if (cmdfile != 0)
        {
            os_fprintz(cmdfile, ">");
            os_fprintz(cmdfile, buf);
            os_fprintz(cmdfile, "\n");
        }


        for (p = buf ; *p != '\0' ; ++p)
            *p = cmap_n2i(*p);


        return retval;
    }
}
