_dir_close_posix(BD_DIR_H *dir)
{
    if (dir) {
        closedir((DIR *)dir->internal);

        BD_DEBUG(DBG_DIR, "Closed POSIX dir (%p)\n", (void*)dir);

        X_FREE(dir);
    }
}
