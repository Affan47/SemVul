check_mount(e2fsck_t ctx)
{
	errcode_t	retval;
	int		cont;

	retval = ext2fs_check_if_mounted(ctx->filesystem_name,
					 &ctx->mount_flags);
	if (retval) {
		com_err("ext2fs_check_if_mount", retval,
			_("while determining whether %s is mounted."),
			ctx->filesystem_name);
		return;
	}


	if ((!(ctx->mount_flags & EXT2_MF_MOUNTED)) ||
	    ((ctx->mount_flags & EXT2_MF_ISROOT) &&
	     (ctx->mount_flags & EXT2_MF_READONLY) &&
	     !(ctx->options & E2F_OPT_WRITECHECK)))
		return;

	if ((ctx->options & E2F_OPT_READONLY) &&
	    !(ctx->options & E2F_OPT_WRITECHECK)) {
		printf(_("Warning!  %s is mounted.\n"), ctx->filesystem_name);
		return;
	}

	printf(_("%s is mounted.  "), ctx->filesystem_name);
	if (!ctx->interactive)
		fatal_error(ctx, _("Cannot continue, aborting.\n\n"));
	printf(_("\n\n\007\007\007\007WARNING!!!  "
	       "The filesystem is mounted.   If you continue you ***WILL***\n"
	       "cause ***SEVERE*** filesystem damage.\007\007\007\n\n"));
	cont = ask_yn(_("Do you really want to continue"), -1);
	if (!cont) {
		printf (_("check aborted.\n"));
		exit (0);
	}
	return;
}
