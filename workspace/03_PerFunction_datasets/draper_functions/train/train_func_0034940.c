findThemes(const char *path, YMenu *container) {
    char const *const tname("/default.theme");

    int dplen(strlen(path));
    char *npath = NULL, *dpath = NULL;

    if (dplen == 0 || path[dplen - 1] != '/') {
        npath = cstrJoin(path, "/", NULL);
        dplen++;
    } else {
        dpath = newstr(path);
    }

    bool bNesting=nestedThemeMenuMinNumber && themeCount>nestedThemeMenuMinNumber;

    DIR *dir(opendir(path));

    if (dir != NULL) {
        struct dirent *de;
        while ((de = readdir(dir)) != NULL) {

           if(de->d_name[0] == '.')
              continue;

            YMenuItem *im(NULL);
            npath = cstrJoin(dpath, de->d_name, tname, NULL);

            if (npath && access(npath, R_OK) == 0) {
                char *relThemeName = cstrJoin(de->d_name, tname, NULL);
                im = newThemeItem(de->d_name, npath, relThemeName);
                if (im) {
                    if (bNesting)
                    {
                       char fLetter = ASCII::toUpper(de->d_name[0]);

                        int targetItem = container->findFirstLetRef(fLetter, 0, 1);

                        if(targetItem<0)
                        {
                                char *smname = strdup("....");
                                smname[0] = fLetter;

                                YMenu *smenu = new YMenu();
                                YMenuItem *smItem = new YMenuItem(smname, 0, null, NULL, smenu);
                                if(smItem && smenu)
                                   container->addSorted(smItem, false);
                                targetItem = container->findFirstLetRef(fLetter, 0, 1);
                                if(targetItem<0)
                                {
                                   warn("Failed to add submenu");
                                   return;
                                }
                        }
                        container->getItem(targetItem)->getSubmenu()->addSorted(im, false);
                    } else
                        container->addSorted(im, false);
                }
                delete [] relThemeName;
            }

            delete [] npath;

            char *subdir(cstrJoin(dpath, de->d_name, NULL));
            if (im && subdir) findThemeAlternatives(subdir, de->d_name, im);
            delete [] subdir;
        }

        closedir(dir);
    }

    delete [] dpath;
}
