make_array_indices(int_list *index)
{
    int_list_list *indices = new int_list_list;

    DBG(cout << "index: ");
    DBG(copy(index->begin(), index->end(), ostream_iterator<int>(cerr, " ")));
    DBG(cerr << endl);

    assert(index);
    indices->push_back(index);

    return indices;
}
