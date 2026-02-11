fieldName() const
{
	switch(v_type) {
		case username:  return QObject::tr("Username");
		case nick:      return QObject::tr("Nickname");
		case password:  return QObject::tr("Password");
		case name:      return QObject::tr("Name");
		case first:     return QObject::tr("First Name");
		case last:      return QObject::tr("Last Name");
		case email:     return QObject::tr("E-mail");
		case address:   return QObject::tr("Address");
		case city:      return QObject::tr("City");
		case state:     return QObject::tr("State");
		case zip:       return QObject::tr("Zipcode");
		case phone:     return QObject::tr("Phone");
		case url:       return QObject::tr("URL");
		case date:      return QObject::tr("Date");
		case misc:      return QObject::tr("Misc");
		default:        return "";
	};
}
