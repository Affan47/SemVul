ZapConflicts(int device_index, int authoritative_side)
{

	DeviceEntry &entry = (*m_device_set)[device_index];
	OpenSync::Config::Group *group = entry.GetConfigGroup();
	if( !group )
		return false;


	OpenSync::Config::Group::iterator gi = group->begin();
	for( int i = 0; gi != group->end(); ++gi, ++i ) {


		if( i == authoritative_side )
			continue;

		OpenSync::Config::Plugin &plugin = *(*gi);


		ConfigUI::ptr ui = ConfigUI::CreateConfigUI(plugin.GetAppName());
		if( !ui.get() ) {


			continue;
		}

		bool success = ui->ZapData(m_parent, *gi, entry.GetEngine());
		if( !success ) {

			return false;
		}
	}


	return true;
}
