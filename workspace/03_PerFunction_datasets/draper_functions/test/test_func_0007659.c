job_exists(const char *path, job_op mask)
{
    job_store();

    if (db_job_exists(path, mask) != DB_OK)
        return -1;
    return 0;
}
