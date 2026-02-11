add_resource(unsigned long ofs, unsigned long siz,
                                  const char *resname, size_t resnamelen,
                                  int fileno)
{
    CResEntry *entry;


    entry = new CResEntry(resname, resnamelen, TRUE, ofs, siz, fileno);


    restab_->add(entry);
}
