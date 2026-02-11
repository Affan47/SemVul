chdir_root()
{
    int rc = 0;
    if (current_dir)
    {
        rc = ::chdir("/");
        Log::debug("-chdir to \"/\"");
	current_dir = NULL;
    }
    return rc == 0;
}
