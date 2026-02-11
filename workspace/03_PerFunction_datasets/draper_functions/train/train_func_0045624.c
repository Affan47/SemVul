encoder_progress_begin( lame_global_flags const* gf
                      , char              const* inPath
                      , char              const* outPath
                      )
{
    if (silent < 10) {
        lame_print_config(gf);

        console_printf("Encoding %s%s to %s\n",
                       strcmp(inPath, "-") ? inPath : "<stdin>",
                       strlen(inPath) + strlen(outPath) < 66 ? "" : "\n     ",
                       strcmp(outPath, "-") ? outPath : "<stdout>");

        console_printf("Encoding as %g kHz ", 1.e-3 * lame_get_out_samplerate(gf));

        {
            static const char *mode_names[2][4] = {
                {"stereo", "j-stereo", "dual-ch", "single-ch"},
                {"stereo", "force-ms", "dual-ch", "single-ch"}
            };
            switch (lame_get_VBR(gf)) {
            case vbr_rh:
                console_printf("%s MPEG-%u%s Layer III VBR(q=%g) qval=%i\n",
                               mode_names[lame_get_force_ms(gf)][lame_get_mode(gf)],
                               2 - lame_get_version(gf),
                               lame_get_out_samplerate(gf) < 16000 ? ".5" : "",
                               lame_get_VBR_quality(gf),
                               lame_get_quality(gf));
                break;
            case vbr_mt:
            case vbr_mtrh:
                console_printf("%s MPEG-%u%s Layer III VBR(q=%g)\n",
                               mode_names[lame_get_force_ms(gf)][lame_get_mode(gf)],
                               2 - lame_get_version(gf),
                               lame_get_out_samplerate(gf) < 16000 ? ".5" : "",
                               lame_get_VBR_quality(gf));
                break;
            case vbr_abr:
                console_printf("%s MPEG-%u%s Layer III (%gx) average %d kbps qval=%i\n",
                               mode_names[lame_get_force_ms(gf)][lame_get_mode(gf)],
                               2 - lame_get_version(gf),
                               lame_get_out_samplerate(gf) < 16000 ? ".5" : "",
                               0.1 * (int) (10. * lame_get_compression_ratio(gf) + 0.5),
                               lame_get_VBR_mean_bitrate_kbps(gf),
                               lame_get_quality(gf));
                break;
            default:
                console_printf("%s MPEG-%u%s Layer III (%gx) %3d kbps qval=%i\n",
                               mode_names[lame_get_force_ms(gf)][lame_get_mode(gf)],
                               2 - lame_get_version(gf),
                               lame_get_out_samplerate(gf) < 16000 ? ".5" : "",
                               0.1 * (int) (10. * lame_get_compression_ratio(gf) + 0.5),
                               lame_get_brate(gf),
                               lame_get_quality(gf));
                break;
            }
        }

        if (silent <= -10) {
            lame_print_internals(gf);
        }
    }
}
