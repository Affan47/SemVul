cli_groupiconscan(struct ICON_ENV *icon_env, uint32_t rva)
{

    uint32_t resdir_rva = icon_env->resdir_rva;
    cli_ctx *ctx = icon_env->ctx;
    struct cli_exe_section *exe_sections = icon_env->exe_sections;
    uint16_t nsections = icon_env->nsections;
    uint32_t hdr_size = icon_env->hdr_size;

    int err = 0;
    fmap_t *map = *ctx->fmap;
    const uint8_t *grp = fmap_need_off_once(map, cli_rawaddr(rva, exe_sections, nsections, (unsigned int *)(&err), map->len, hdr_size), 16);

    if(grp && !err) {
        uint32_t gsz = cli_readint32(grp + 4);
        if(gsz>6) {
            uint32_t icnt, raddr;
            unsigned int piconcnt;
            struct icondir {
                uint8_t w;
                uint8_t h;
                uint8_t palcnt;
                uint8_t rsvd;
                uint16_t planes;
                uint16_t depth;
                uint32_t sz;
                uint16_t id;
            } *dir;

            raddr = cli_rawaddr(cli_readint32(grp), exe_sections, nsections, (unsigned int *)(&err), map->len, hdr_size);
            cli_dbgmsg("cli_scanicon: icon group @%x\n", raddr);
            grp = fmap_need_off_once(map, raddr, gsz);
            if(grp && !err) {
                icnt = cli_readint32(grp+2) >> 16;

                grp += 6;
                gsz -= 6;

                while(icnt && gsz >= 14 ) {
                    piconcnt = icon_env->hcnt;

                    dir = (struct icondir *)grp;
                    cli_dbgmsg("cli_scanicon: Icongrp @%x - %ux%ux%u - (id=%x, rsvd=%u, planes=%u, palcnt=%u, sz=%x)\n", rva, dir->w, dir->h, cli_readint16(&dir->depth), cli_readint16(&dir->id), cli_readint16(&dir->planes), dir->palcnt, dir->rsvd, cli_readint32(&dir->sz));


                    findres(3, cli_readint16(&dir->id), resdir_rva, map, exe_sections, nsections, hdr_size, icon_scan_cb, icon_env);
                    if (icon_env->result != CL_CLEAN)
                        return icon_env->result;

                    if (piconcnt == icon_env->hcnt)
                        cli_dbgmsg("cli_scanicon: invalid icon entry %u in group @%x\n", dir->id, rva);

                    icon_env->icnt++;
                    icnt--;

                    if (icon_env->icnt >= icon_env->max_icons) {
                        icon_env->result = CL_EMAXSIZE;
                        return icon_env->result;
                    }

                    grp += 14;
                    gsz -= 14;
                }

                if (icnt != 0)
                    cli_dbgmsg("cli_scanicon: could not find %u icons\n", icnt);
                if (gsz != 0)
                    cli_dbgmsg("cli_scanicon: could not parse %u bytes of icon entries\n", gsz);
            }
        }
    }

    return icon_env->result;
}
