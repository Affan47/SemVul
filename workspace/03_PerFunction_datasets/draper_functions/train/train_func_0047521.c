main(int argc, char **argv)
{
    struct passwd *p;

    while ((p = getpwent()) != NULL)
#ifdef ZOS_USS
        printf("%s:%ld:%ld:%s:%s\n",
            p->pw_name, (long) p->pw_uid,
            (long) p->pw_gid, p->pw_dir, p->pw_shell);
#else
        printf("%s:%s:%ld:%ld:%s:%s:%s\n",
            p->pw_name, p->pw_passwd, (long) p->pw_uid,
            (long) p->pw_gid, p->pw_gecos, p->pw_dir, p->pw_shell);
#endif

    endpwent();
    return 0;
}
