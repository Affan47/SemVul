job_remove(job_t *j)
{
    job_list_t::iterator iter = std::find(my_job_list.begin(), my_job_list.end(), j);
    if (iter != my_job_list.end())
    {
        my_job_list.erase(iter);
        return true;
    }
    else
    {
        debug(1, _(L"Job inconsistency"));
        sanity_lose();
        return false;
    }
}
