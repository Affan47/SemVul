notify_created(Interest *ip)
{
    if (!ip)
	ip = this;
    myfilesystem->ll_notify_created(ip);
}
