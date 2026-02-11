volgen_write_volfile (volgen_graph_t *graph, char *filename)
{
        char        *ftmp = NULL;
        FILE        *f = NULL;
        int          fd   = 0;
        xlator_t    *this = NULL;

        this = THIS;

        if (gf_asprintf (&ftmp, "%s.tmp", filename) == -1) {
                ftmp = NULL;

                goto error;
        }

        fd = creat (ftmp, S_IRUSR | S_IWUSR);
        if (fd < 0) {
                gf_log (this->name, GF_LOG_ERROR, "%s",
                        strerror (errno));
                goto error;
        }

        close (fd);

        f = fopen (ftmp, "w");
        if (!f)
                goto error;

        if (glusterfs_graph_print_file (f, &graph->graph) == -1)
                goto error;

        if (fclose (f) != 0) {
                gf_log (THIS->name, GF_LOG_ERROR, "fclose on the file %s "
                        "failed (%s)", ftmp, strerror (errno));


                f = NULL;
                goto error;
        }

        f = NULL;

        if (rename (ftmp, filename) == -1)
                goto error;

        GF_FREE (ftmp);

	volgen_apply_filters(filename);

        return 0;

 error:

        GF_FREE (ftmp);
        if (f)
                fclose (f);

        gf_log (this->name, GF_LOG_ERROR,
                "failed to create volfile %s", filename);

        return -1;
}
