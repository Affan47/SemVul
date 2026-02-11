sgi_check_bootfile(struct fdisk_context *cxt, const char *name)
{
	size_t sz;
	struct sgi_disklabel *sgilabel = self_disklabel(cxt);

	sz = strlen(name);

	if (sz < 3) {

		fdisk_warnx(cxt, _("Invalid bootfile!  The bootfile must "
				   "be an absolute non-zero pathname, "
				   "e.g. \"/unix\" or \"/unix.save\"."));
		return -EINVAL;

	} else if (sz > sizeof(sgilabel->boot_file)) {
		fdisk_warnx(cxt, P_("Name of bootfile is too long: %zu byte maximum.",
				    "Name of bootfile is too long: %zu bytes maximum.",
				    sizeof(sgilabel->boot_file)),
			    sizeof(sgilabel->boot_file));
		return -EINVAL;

	} else if (*name != '/') {
		fdisk_warnx(cxt, _("Bootfile must have a fully qualified pathname."));
		return -EINVAL;
	}

	if (strncmp(name, (char *) sgilabel->boot_file,
				sizeof(sgilabel->boot_file))) {
		fdisk_warnx(cxt, _("Be aware that the bootfile is not checked "
				   "for existence.  SGI's default is \"/unix\", "
				   "and for backup \"/unix.save\"."));
		return 0;
	}

	return 1;
}
