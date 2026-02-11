keyring_delete_keyblock (KEYRING_HANDLE hd)
{
    int rc;

    if (!hd->found.kr)
        return -1;

    if (!hd->found.n_packets) {

        rc = keyring_get_keyblock (hd, NULL);
        if (rc) {
            log_error ("re-reading keyblock failed: %s\n", g10_errstr (rc));
            return rc;
        }
        if (!hd->found.n_packets)
            BUG ();
    }


    iobuf_close (hd->current.iobuf);
    hd->current.iobuf = NULL;


    rc = do_copy (2, hd->found.kr->fname, NULL, hd->secret,
                  hd->found.offset, hd->found.n_packets );
    if (!rc) {

        hd->found.kr = NULL;
        hd->found.offset = 0;


    }
    return rc;
}
