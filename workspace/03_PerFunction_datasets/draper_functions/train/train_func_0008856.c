job_set_owner_and_group(lListElem *job, u_long32 uid, u_long32 gid,
                        const char *user, const char *group) {
   bool ret = true;

   DENTER(TOP_LAYER, "job_set_owner_and_group");
   lSetString(job, JB_owner, user);
   lSetUlong(job, JB_uid, uid);
   lSetString(job, JB_group, group);
   lSetUlong(job, JB_gid, gid);
   DRETURN(ret);
}
