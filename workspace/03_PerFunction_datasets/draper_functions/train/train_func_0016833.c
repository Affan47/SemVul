getDescription(Rules& r){
	Q_UNUSED(r);

	QString begin=QString("");
	if(!active)
		begin="X - ";

	QString end=QString("");
	if(!comments.isEmpty())
		end=", "+tr("C: %1", "Comments").arg(comments);

	QString s=tr("Activity tag preferred rooms"); s+=", ";
	s+=tr("WP:%1\%", "Weight percentage").arg(CustomFETString::number(this->weightPercentage));s+=", ";
	s+=tr("AT:%1", "Activity tag").arg(this->activityTagName);
	for(QStringList::Iterator it=this->roomsNames.begin(); it!=this->roomsNames.end(); it++){
		s+=", ";
		s+=tr("R:%1", "Room").arg(*it);
	}

	return begin+s+end;
}
