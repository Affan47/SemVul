maybe_download(PanelApplet *applet)
{

  if(state==IDLE && !reloading && can_upgrade)
    {
      DownloadUpgrades download=get_download_upgrades(applet);

      if(download == DOWNLOAD_ALL ||
	 (download == DOWNLOAD_SECURITY && security_upgrades_available))
	{
	  write_download_msg(to_slave, download==DOWNLOAD_ALL);
	  set_state(DOWNLOADING, applet);
	}
    }
}
