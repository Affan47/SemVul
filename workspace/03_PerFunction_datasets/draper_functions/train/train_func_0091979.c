print_version_info(struct augeas *aug) {
    const char *version;
    int r;

    r = aug_get(aug, "/augeas/version", &version);
    if (r != 1)
        goto error;

    fprintf(stderr, "augparse %s <http://augeas.net/>\n", version);
    fprintf(stderr, "Copyright (C) 2007-2011 David Lutterkort\n");
    fprintf(stderr, "License LGPLv2+: GNU LGPL version 2.1 or later\n");
    fprintf(stderr, "                 <http://www.gnu.org/licenses/lgpl-2.1.html>\n");
    fprintf(stderr, "This is free software: you are free to change and redistribute it.\n");
    fprintf(stderr, "There is NO WARRANTY, to the extent permitted by law.\n\n");
    fprintf(stderr, "Written by David Lutterkort\n");
    return;
 error:
    fprintf(stderr, "Something went terribly wrong internally - please file a bug\n");
}
