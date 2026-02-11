getLinkedMoleculeCodes(const int atc_id) const
{
    return d->m_AtcToMol.values(atc_id).toVector();
}
