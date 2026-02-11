upd_facedir(Entry *ce, Section *cs ATTR_UNUSED)
{
    char *oldpic, *newpic, *olddir;
    struct passwd *pw;

    if (use_destdir)
        return;
    if (oldkdepfx) {

        ASPrintf(&olddir, "%s/share/apps/kdm/faces", oldkdepfx);
        if (ce->active && strcmp(olddir, ce->value))

            return;

        ce->active = False;

        if (!strcmp(olddir, def_FaceDir))
            olddir = 0;
    } else {
        olddir = 0;
    }
    if (mkdirp(def_FaceDir, 0755, "user face", True)) {
        const char *defpic = def_FaceDir "/.default.face.icon";
        const char *rootpic = def_FaceDir "/root.face.icon";
        if (oldkde && (!olddir || !copyDir(olddir, def_FaceDir)) &&
            oldver < 0x0201)
        {
            setpwent();
            while ((pw = getpwent()))
                if (strcmp(pw->pw_name, "root")) {
                    ASPrintf(&oldpic, "%s/share/apps/kdm/pics/users/%s.png",
                             oldkdepfx, pw->pw_name);
                    ASPrintf(&newpic, def_FaceDir "/%s.face.icon", pw->pw_name);
                    rename(oldpic, newpic);
                    free(newpic);
                    free(oldpic);
                }
            endpwent();
            ASPrintf(&oldpic, "%s/share/apps/kdm/pics/users/default.png", oldkdepfx);
            if (!rename(oldpic, defpic))
                defpic = 0;
            ASPrintf(&oldpic, "%s/share/apps/kdm/pics/users/root.png", oldkdepfx);
            if (!rename(oldpic, rootpic))
                rootpic = 0;
        }
        if (defpic) {
            ASPrintf(&oldpic, "%s/default1.png", facesrc);
            copyPlainFile(oldpic, defpic);
        }
        if (rootpic) {
            ASPrintf(&oldpic, "%s/root1.png", facesrc);
            copyPlainFile(oldpic, rootpic);
        }
    }
}
