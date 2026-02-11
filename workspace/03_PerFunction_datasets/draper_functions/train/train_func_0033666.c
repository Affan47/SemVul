setOutfile(const char *name, const char *dir, const char *arg, const char *ext)
{
    const char *docfilename;

    if (name)
    {
        docfilename = name;
    }
    else
    {
        const char *argdoc;
        if (global.params.preservePaths)
            argdoc = arg;
        else
            argdoc = FileName::name(arg);


        if (!FileName::absolute(argdoc))
        {
            argdoc = FileName::combine(dir, argdoc);
        }
        docfilename = FileName::forceExt(argdoc, ext);
    }

    if (FileName::equals(docfilename, srcfile->name->str))
    {   error("Source file and output file have same name '%s'", srcfile->name->str);
        fatal();
    }

    return new File(docfilename);
}
