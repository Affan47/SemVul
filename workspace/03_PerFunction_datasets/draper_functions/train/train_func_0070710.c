pdbioSeqresToSequence(const AjPStr seqres,
                                    AjPStr *seq, AjBool camask,
                                    ajuint *len)
{
    const AjPStr aa3 = NULL;
    char aa1 = '\0';
    ajuint nrem = 0;


    if (!seqres || !seq)
    {
        ajWarn("Bad args passed to pdbioSeqresToSequence\n");

        return ajFalse;
    }


    if ((aa3 = ajStrParseC(seqres, " \n")))
    {

        do
        {
            if (ajStrMatchC(aa3, "FOR") ||
                ajStrMatchC(aa3, "ACE") ||
                ajStrMatchC(aa3, "NH2"))
            {
                if (camask)
                {
                    nrem++;
                    continue;
                }
            }

            ajResidueFromTriplet(aa3, &aa1);
            ajStrAppendK(seq, aa1);
        }
        while ((aa3 = ajStrParseC(NULL, " \n")));
    }
    else
        return ajFalse;

    *len = ajStrGetLen(*seq) + nrem;

    return ajTrue;
}
