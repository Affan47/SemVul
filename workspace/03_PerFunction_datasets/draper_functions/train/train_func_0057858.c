cli_mbr_check2(cli_ctx *ctx, size_t sectorsize) {
    struct mbr_boot_record mbr;
    off_t pos = 0, mbr_base = 0;
    size_t maplen;

    if (!ctx || !ctx->fmap) {
        cli_errmsg("cli_scanmbr: Invalid context\n");
        return CL_ENULLARG;
    }


    if (sectorsize == 0)
        sectorsize = MBR_SECTOR_SIZE;

    mbr_base = sectorsize - sizeof(struct mbr_boot_record);


    maplen = (*ctx->fmap)->real_len;
    if ((maplen % sectorsize) != 0) {
        cli_dbgmsg("cli_scanmbr: File sized %lu is not a multiple of sector size %lu\n",
                   (unsigned long)maplen, (unsigned long)sectorsize);
        return CL_EFORMAT;
    }


    pos = (MBR_SECTOR * sectorsize) + mbr_base;


    if (fmap_readn(*ctx->fmap, &mbr, pos, sizeof(mbr)) != sizeof(mbr)) {
        cli_dbgmsg("cli_scanmbr: Invalid master boot record\n");
        return CL_EFORMAT;
    }


    mbr_convert_to_host(&mbr);

    if ((mbr.entries[0].type == MBR_PROTECTIVE) || (mbr.entries[0].type == MBR_HYBRID))
        return CL_TYPE_GPT;

    return mbr_check_mbr(&mbr, maplen, sectorsize);
}
