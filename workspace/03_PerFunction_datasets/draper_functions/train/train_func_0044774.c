lookForSourceFile(const char *filename)
{


    const char *sdi = FileName::forceExt(filename, global.hdr_ext);
    if (FileName::exists(sdi) == 1)
        return sdi;

    const char *sd  = FileName::forceExt(filename, global.mars_ext);
    if (FileName::exists(sd) == 1)
        return sd;

    if (FileName::exists(filename) == 2)
    {


        const char *n = FileName::combine(filename, "package.d");
        if (FileName::exists(n) == 1)
            return n;
        FileName::free(n);
    }

    if (FileName::absolute(filename))
        return NULL;

    if (!global.path)
        return NULL;

    for (size_t i = 0; i < global.path->dim; i++)
    {
        const char *p = (*global.path)[i];

        const char *n = FileName::combine(p, sdi);
        if (FileName::exists(n) == 1)
            return n;
        FileName::free(n);

        n = FileName::combine(p, sd);
        if (FileName::exists(n) == 1)
            return n;
        FileName::free(n);

        const char *b = FileName::removeExt(filename);
        n = FileName::combine(p, b);
        FileName::free(b);
        if (FileName::exists(n) == 2)
        {
            const char *n2 = FileName::combine(n, "package.d");
            if (FileName::exists(n2) == 1)
                return n2;
            FileName::free(n2);
        }
        FileName::free(n);
    }
    return NULL;
}
