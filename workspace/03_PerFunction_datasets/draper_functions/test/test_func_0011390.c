kui_manager_cangetkey(struct kui_manager *kuim)
{
    if (!kuim)
        return -1;


    return kui_cangetkey(kuim->terminal_keys) ||
            kui_cangetkey(kuim->normal_keys);
}
