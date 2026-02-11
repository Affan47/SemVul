use_r_out(void)
{
    char *mpfilename, cmd[1000];

    mpfilename = G_tempfile();
    write_params(mpfilename, vfiles[0], outfile, frames, quality, 0, 0, 1);

    if (quiet)
	sprintf(cmd, "%s %s 2> /dev/null > /dev/null", encoder, mpfilename);
    else
	sprintf(cmd, "%s %s", encoder, mpfilename);

    if (0 != G_system(cmd))
	G_warning(_("mpeg_encode ERROR"));

    clean_files(mpfilename, NULL, 0);

    return (1);
}
