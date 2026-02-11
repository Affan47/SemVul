glusterd_unlock (uuid_t uuid)
{
        uuid_t  owner;
        char    new_owner_str[50];
        char    owner_str[50];
        int32_t ret = -1;

        GF_ASSERT (uuid);

        glusterd_get_lock_owner (&owner);

        if (NULL == owner) {
                gf_log ("glusterd", GF_LOG_ERROR, "Cluster lock not held!");
                goto out;
        }

        ret = uuid_compare (uuid, owner);

        if (ret) {
               gf_log ("glusterd", GF_LOG_ERROR, "Cluster lock held by %s"
                        " ,unlock req from %s!", uuid_utoa_r (owner ,owner_str)
                        , uuid_utoa_r (uuid, new_owner_str));
               goto out;
        }

        ret = glusterd_unset_lock_owner (uuid);

        if (ret) {
                gf_log ("glusterd", GF_LOG_ERROR, "Unable to clear cluster "
                        "lock");
                goto out;
        }

        ret = 0;

out:
        return ret;
}
