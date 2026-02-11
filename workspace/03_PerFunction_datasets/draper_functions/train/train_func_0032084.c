handle_remove(const char* name) {
    DB_VDA_FILE vf;
    char buf[1024];
    sprintf(buf, "where file_name='%s'", name);
    int retval = vf.lookup(buf);
    if (retval) return retval;


    DB_VDA_CHUNK_HOST ch;
    sprintf(buf, "vda_file_id=%d", vf.id);
    ch.delete_from_db_multi(buf);
    vf.delete_from_db();


    dir_hier_path(name, config.download_dir, config.uldl_dir_fanout, buf);
    unlink(buf);


    retval = chdir(vf.dir);
    if (retval) perror("chdir");
    retval = system("/bin/rm -rf [0-9]* Coding data.vda chunk_sizes.txt");
    if (retval) perror("system");
    return 0;
}
