getGroupName() {
		QString group;
		if ( cvi->type() == Profile )
			group = "/\\/" + profileName + "\\/\\";
		else
			group = groupName;

		return group;
	}
