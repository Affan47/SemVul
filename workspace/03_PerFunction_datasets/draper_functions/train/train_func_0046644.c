bifftell(bifcxdef *ctx, int argc)
{
    osfildef *fp;


    bifcntargs(ctx, 1, argc);
    fp = bif_get_file(ctx, (int *)0, 0);


    runpnum(ctx->bifcxrun, osfpos(fp));
}
