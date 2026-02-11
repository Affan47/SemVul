locations_are_equal(const location *l1, const location *l2)
{
    return ((l1->first_line == l2->first_line) && (strcmp(l1->file, l2->file) == 0));
}
