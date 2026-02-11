ReadSequence ( str  file,
                              UINT line )

{
    str seq = NULL;

    if (file && *file)
    {
        ifstream input (file);

        if (input)
        {
            int error = 0;
            str tmp   = NULL;

            while (!error && line)
            {
                if (tmp) delete tmp, tmp = NULL;


                line--;
            }

            if (error && tmp)
            {
                if      (line)         delete tmp, tmp = NULL;
                else if (!input.eof()) delete tmp, tmp = NULL;
            }

            if (((seq = tmp)              != NULL) &&
                ((tmp = strchr(seq,'\n')) != NULL)) *tmp = 0;
        }
    }

    return seq;
}
