sge_make_tmpdir(
lListElem *qep,
u_long32 jobid,
u_long32 jataskid,
uid_t uid,
gid_t gid,
char *tmpdir
) {
   const char *t;

   DENTER(TOP_LAYER, "sge_make_tmpdir");

   if (!(t=lGetString(qep, QU_tmpdir))) {
      DEXIT;
      return NULL;
   }


   sprintf(tmpdir, "%s/"sge_u32"."sge_u32".%s", t, jobid, jataskid, lGetString(qep, QU_qname));

   DPRINTF(("making TMPDIR=%s\n", tmpdir));

   sge_switch2start_user();
   sge_mkdir(tmpdir, 0755, 0, 0);


   chown(tmpdir, uid, gid);
   sge_switch2admin_user();

   DEXIT;
   return tmpdir;
}
