smsc2_restart_smsc(Octstr *id)
{
    CfgGroup *grp;
    SMSCConn *conn, *new_conn;
    Octstr *smscid = NULL;
    long i = -1;
    int hit;
    int num = 0;
    int success = 0;

    if (!smsc_running)
        return -1;

    gw_rwlock_wrlock(&smsc_list_lock);

    if (bb_reload_smsc_groups() != 0) {
        gw_rwlock_unlock(&smsc_list_lock);
        return -1;
    }

    while((i = smsc2_find(id, ++i)) != -1) {
        long group_index;

        conn = gwlist_get(smsc_list, i);
        if (conn != NULL && smscconn_status(conn) != SMSCCONN_DEAD) {
            warning(0, "HTTP: Could not re-start already running smsc-id `%s'",
                octstr_get_cstr(id));
            continue;
        }

        hit = -1;
        grp = NULL;
        for (group_index = 0; group_index < gwlist_len(smsc_groups) &&
             (grp = gwlist_get(smsc_groups, group_index)) != NULL; group_index++) {
            smscid = cfg_get(grp, octstr_imm("smsc-admin-id"));
            if (smscid == NULL)
            smscid = cfg_get(grp, octstr_imm("smsc-id"));
            if (smscid != NULL && octstr_compare(smscid, id) == 0) {
                if (hit < 0)
                    hit = 0;
                if (hit == num)
                    break;
                else
                    hit++;
            }
            octstr_destroy(smscid);
            smscid = NULL;
        }
        octstr_destroy(smscid);
        if (hit != num) {

            error(0, "HTTP: Could not find config for smsc-id `%s'", octstr_get_cstr(id));
            break;
        }

        info(0,"HTTP: Re-starting smsc-id `%s'", octstr_get_cstr(id));

        new_conn = smscconn_create(grp, 1);
        if (new_conn == NULL) {
            error(0, "Start of SMSC connection failed, smsc-id `%s'", octstr_get_cstr(id));
            continue;
        }


        gwlist_delete(smsc_list, i, 1);

        smscconn_destroy(conn);
        gwlist_insert(smsc_list, i, new_conn);
        smscconn_start(new_conn);
        success = 1;
        num++;
    }

    gw_rwlock_unlock(&smsc_list_lock);

    if (success == 0) {
        error(0, "SMSC %s not found", octstr_get_cstr(id));
        return -1;
    }

    if (router_thread >= 0)
        gwthread_wakeup(router_thread);
    return 0;
}
