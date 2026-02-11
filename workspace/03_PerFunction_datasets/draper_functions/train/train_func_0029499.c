DeleteSharedIPGroup(RakNet::RakString groupId)
{
	AddOperation(RO_DELETE_SHARED_IP_GROUP, "DELETE", RakNet::RakString("shared_ip_groups/%s", groupId.C_String()), "");
}
