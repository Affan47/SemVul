gssint_mecherrmap_map(OM_uint32 minor, const gss_OID_desc * oid)
{
    const struct mecherror *mep;
    struct mecherror me, me_copy;
    const OM_uint32 *p;
    int err;
    OM_uint32 new_status;

#ifdef DEBUG
    FILE *f;
    f = fopen("/dev/pts/9", "w+");
    if (f == NULL)
        f = stderr;
#endif

    me.code = minor;
    me.mech = *oid;
    k5_mutex_lock(&mutex);


    p = mecherrmap_findright(&m, me);
    if (p != NULL) {
        k5_mutex_unlock(&mutex);
#ifdef DEBUG
        fprintf(f, "%s: found ", __FUNCTION__);
        mecherror_print(me, f);
        fprintf(f, " in map as %lu\n", (unsigned long) *p);
        if (f != stderr) fclose(f);
#endif
        return *p;
    }


    mep = mecherrmap_findleft(&m, minor);
    if (mep == NULL) {

        new_status = minor;
    } else {


        do {
            next_fake++;
            new_status = next_fake;
            if (new_status == 0)
                ;
        } while (mecherrmap_findleft(&m, new_status) != NULL);
    }
    err = mecherror_copy(&me_copy, me);
    if (err) {
        k5_mutex_unlock(&mutex);
        return err;
    }
    err = mecherrmap_add(&m, new_status, me_copy);
    k5_mutex_unlock(&mutex);
    if (err)
        free(me_copy.mech.elements);
#ifdef DEBUG
    fprintf(f, "%s: mapping ", __FUNCTION__);
    mecherror_print(me, f);
    fprintf(f, " to %lu: err=%d\nnew map: ", (unsigned long) new_status, err);
    mecherrmap_printmap(&m, f);
    fprintf(f, "\n");
    if (f != stderr) fclose(f);
#endif
    if (err)
        return 0;
    else
        return new_status;
}
