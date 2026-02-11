getFileDocument(u_int ix) const
{
    return (ix < files->length() ? (*files)[ix].doc : fxStr::null);
}
