queryStopCommand(QString const & cmd)
{
	docstring text = bformat(_(
		"The command\n%1$s\nhas not yet completed.\n\n"
		"Do you want to stop it?"), qstring_to_ucs4(cmd));
	return ProgressInterface::instance()->prompt(_("Stop command?"), text,
			1, 1, _("&Stop it"), _("Let it &run")) == 0;
}

}
