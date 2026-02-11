bifoph(bifcxdef *ctx, int argc)
{
    runsdef val;
    int     hidden, output_occurred;

    bifcntargs(ctx, 1, argc);
    outstat(&hidden, &output_occurred);
    if (runtostyp(ctx->bifcxrun) == DAT_TRUE)
    {

        rundisc(ctx->bifcxrun);


        if (!hidden)
            val.runsv.runsvnum = 0;
        else if (!output_occurred)
            val.runsv.runsvnum = 1;
        else
            val.runsv.runsvnum = 2;
        runpush(ctx->bifcxrun, DAT_NUMBER, &val);


        outhide();
    }
    else if (runtostyp(ctx->bifcxrun) == DAT_NIL)
    {

        rundisc(ctx->bifcxrun);


        runpush(ctx->bifcxrun, runclog(outshow()), &val);
    }
    else if (runtostyp(ctx->bifcxrun) == DAT_NUMBER)
    {
        int n = runpopnum(ctx->bifcxrun);

        if (n == 0)
        {

            runpush(ctx->bifcxrun, runclog(outshow()), &val);
        }
        else if (n == 1)
        {


            runpush(ctx->bifcxrun, runclog(output_occurred), &val);
        }
        else if (n == 2)
        {


            runpush(ctx->bifcxrun, runclog(output_occurred), &val);
            outsethidden();
        }
        else
            errsig1(ctx->bifcxerr, ERR_INVVBIF, ERRTSTR, "outhide");
    }
    else
        errsig(ctx->bifcxerr, ERR_REQNUM);
}
