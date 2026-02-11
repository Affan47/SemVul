ajDirNewPathPreExt(const AjPStr path,
                          const AjPStr prefix, const AjPStr ext)
{
    AjPDir thys;

    AJNEW0(thys);
    ajStrAssignS(&thys->Name, path);
    filePrintname(thys->Name, &thys->Printname);

    if (ajStrMatchC(prefix, " "))
        ajStrAssignC(&thys->Prefix, "");
    else if (ajStrGetLen(prefix))
        ajStrAssignS(&thys->Prefix, prefix);

    if (ajStrMatchC(ext, " "))
        ajStrAssignC(&thys->Extension, "");
    else if (ajStrGetLen(ext))
        ajStrAssignS(&thys->Extension, ext);

    return thys;
}
