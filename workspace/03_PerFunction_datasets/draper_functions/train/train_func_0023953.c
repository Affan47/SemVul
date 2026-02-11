unshare_all_internal(USER * user)
{
    if(user->shared)
    {
#ifndef ROUTING_ONLY
        if(ISUSER(user->con))
        {

            free_hash(user->con->uopt->files);
            user->con->uopt->files = 0;
            ASSERT(global.localSharedFiles >= user->shared);
            global.localSharedFiles -= user->shared;
        }
#endif
        if(user->libsize > global.fileLibSize)
        {
            log_message_level( LOG_LEVEL_SHARE, "unshare_all: sender->libsize=%u global.fileLibSize=%f", user->libsize, global.fileLibSize);
            global.fileLibSize = user->libsize;
        }
        ASSERT(global.fileLibSize >= user->libsize);
        global.fileLibSize -= user->libsize;
        ASSERT(global.fileLibCount >= user->shared);
        global.fileLibCount -= user->shared;
        user->libsize = 0;
        user->shared = 0;
    }
}
