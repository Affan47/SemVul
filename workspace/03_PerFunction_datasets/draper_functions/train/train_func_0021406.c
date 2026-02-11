lame_mp3_tags_fid(lame_global_flags * gfp, FILE * fpStream)
{
    lame_internal_flags *gfc;
    SessionConfig_t const *cfg;
    if (!is_lame_global_flags_valid(gfp)) {
        return;
    }
    gfc = gfp->internal_flags;
    if (!is_lame_internal_flags_valid(gfc)) {
        return;
    }
    cfg = &gfc->cfg;
    if (!cfg->write_lame_tag) {
        return;
    }

    if (fpStream && !fseek(fpStream, 0, SEEK_SET)) {
        int     rc = PutVbrTag(gfp, fpStream);
        switch (rc) {
        default:

            break;

        case -1:
            ERRORF(gfc, "Error: could not update LAME tag.\n");
            break;

        case -2:
            ERRORF(gfc, "Error: could not update LAME tag, file not seekable.\n");
            break;

        case -3:
            ERRORF(gfc, "Error: could not update LAME tag, file not readable.\n");
            break;
        }
    }
}
