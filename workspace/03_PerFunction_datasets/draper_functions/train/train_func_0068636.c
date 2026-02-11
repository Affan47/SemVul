lookups(const Vector<int> &required_fids, const Vector<int> &fids, const Vector<Tag> &sorted_ftags, Vector<int> &results, ErrorHandler *errh) const
{
    Vector<int> fidsx(fids);
    filter(fidsx, sorted_ftags);
    for (int i = 0; i < required_fids.size(); i++)
	fidsx.push_back(required_fids[i]);
    return lookups(fidsx, results, errh);
}
