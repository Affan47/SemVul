gp_enumerate_fonts_next(void *enum_state, char **fontname, char **path)
{
#ifdef HAVE_FONTCONFIG
    unix_fontenum_t* state = (unix_fontenum_t *)enum_state;
    FcChar8 *file_fc = NULL;
    FcChar8 *family_fc = NULL;
    int outline_fc, slant_fc, weight_fc;
    FcPattern *font;
    FcResult result;

    if (state == NULL) {
        return 0;
    }

    if (state->index == state->font_list->nfont) {
        return 0;
    }


    font = state->font_list->fonts[state->index];

    result = FcPatternGetString (font, FC_FAMILY, 0, &family_fc);
    if (result != FcResultMatch || family_fc == NULL) {
        dmlprintf(state->mem, "DEBUG: FC_FAMILY mismatch\n");
        return 0;
    }

    result = FcPatternGetString (font, FC_FILE, 0, &file_fc);
    if (result != FcResultMatch || file_fc == NULL) {
        dmlprintf(state->mem, "DEBUG: FC_FILE mismatch\n");
        return 0;
    }

    result = FcPatternGetBool (font, FC_OUTLINE, 0, &outline_fc);
    if (result != FcResultMatch) {
        dmlprintf1(state->mem, "DEBUG: FC_OUTLINE failed to match on %s\n", (char*)family_fc);
        return 0;
    }

    result = FcPatternGetInteger (font, FC_SLANT, 0, &slant_fc);
    if (result != FcResultMatch) {
        dmlprintf(state->mem, "DEBUG: FC_SLANT didn't match\n");
        return 0;
    }

    result = FcPatternGetInteger (font, FC_WEIGHT, 0, &weight_fc);
    if (result != FcResultMatch) {
        dmlprintf(state->mem, "DEBUG: FC_WEIGHT didn't match\n");
        return 0;
    }


    makePSFontName((char *)family_fc, weight_fc, slant_fc,
        (char *)&state->name, sizeof(state->name));
    *fontname = (char *)&state->name;


    *path = (char*)file_fc;

    state->index ++;
    return 1;
#else
    return 0;
#endif
}
