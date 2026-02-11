lcrt_user_del_one(struct lcrt_user *luser, struct lcrtc_user *user, int del_from_db)
{
    if (del_from_db) {
        luser->db.exec(&luser->db,
                   "DELETE FROM %s WHERE name='%s'",
                   luser->get_tb(luser),
                   user->name);
    }
    lcrtc_user_destroy(user);
    luser->db.close(&luser->db);
    return LCRTE_OK;
}
