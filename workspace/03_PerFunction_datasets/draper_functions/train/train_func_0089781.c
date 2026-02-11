add_new_agreement(Slapi_Entry *e)
{
    int rc = 0;
    Repl_Agmt *ra = agmt_new_from_entry(e);
    Slapi_DN *replarea_sdn = NULL;
    Replica *replica = NULL;
    Object *repl_obj = NULL;
    Object *ro = NULL;


    if (ra == NULL)
        return 1;

    ro = object_new((void *)ra, agmt_delete);
    objset_add_obj(agmt_set, ro);
    object_release(ro);


    replarea_sdn = agmt_get_replarea(ra);
    repl_obj = replica_get_replica_from_dn(replarea_sdn);
    slapi_sdn_free(&replarea_sdn);
    if (repl_obj) {
        replica = (Replica*)object_get_data (repl_obj);
    }

    rc = replica_start_agreement(replica, ra);

    if (repl_obj) object_release(repl_obj);

    return rc;
}
