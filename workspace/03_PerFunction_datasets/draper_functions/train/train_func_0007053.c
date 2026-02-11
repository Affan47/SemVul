nfs3_free_readdir3res (readdir3res *res)
{
        entry3 *ent = NULL;
        entry3 *next = NULL;

        if (!res)
                return;

        ent = res->readdir3res_u.resok.reply.entries;
        while (ent) {

                next = ent->nextentry;
                GF_FREE (ent->name);
                GF_FREE (ent);
                ent = next;
        }

        return;
}
