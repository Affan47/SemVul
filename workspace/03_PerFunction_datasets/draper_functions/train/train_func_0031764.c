simple_report (struct prog_ctx *ctx)
{
    edac_mc *mc;
    struct edac_mc_info info;
    unsigned int ue;
    unsigned int ce;

    ue = ce = 0;

    edac_for_each_mc_info (ctx->edac, mc, info) {

        if (!ctx->quiet || info.ce_count)
            fprintf (stdout, "%s: Correctable errors:   %u\n",
                    info.id, info.ce_count);
        if (!ctx->quiet || info.ue_count)
            fprintf (stdout, "%s: Uncorrectable errors: %u\n",
                    info.id, info.ue_count);

        ue += info.ue_count;
        ce += info.ce_count;
    }

    if (!ctx->quiet || ce)
        fprintf (stdout, "Total CE: %u\n", ce);
    if (!ctx->quiet || ue)
        fprintf (stdout, "Total UE: %u\n", ue);

    edac_handle_reset (ctx->edac);

    return;
}
