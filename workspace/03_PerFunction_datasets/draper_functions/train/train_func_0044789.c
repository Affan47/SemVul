addToGroup(const char* name, Symbol groupID)
{
    GroupManager *gmgr = (GroupManager*)
	this->getNetwork()->getGroupManagers()->findDefinition(groupID);
    ASSERT(gmgr);

    if (!gmgr->hasGroup(name))
	gmgr->createGroup (name, this->getNetwork());

    GroupRecord *grec = gmgr->getGroup (name);
    ASSERT(grec);

    this->setGroupName (grec, groupID);
}
