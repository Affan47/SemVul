is_free(const direntry_t* direntry)
{

    return direntry->attributes == 0 || direntry->name[0]==0xe5;
}
