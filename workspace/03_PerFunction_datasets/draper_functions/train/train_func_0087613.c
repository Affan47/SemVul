getIcon(DeviceTypes::Type type)
{
    if  (sDeviceIcons.empty())
    {
        std::string iconsPath = Environment::getIconsPath();
        for (int i=0; i<NUM_DEVICES; i++)
        {
            QString iPath = iconsPath.c_str();
            iPath += sDeviceIconNames[i];
            hOutDebug(5,i <<" ipath:"<<iPath.toStdString());
			sDeviceIcons.push_back(QIcon(iPath));
        }
    }
	return sDeviceIcons.at(type);
}
