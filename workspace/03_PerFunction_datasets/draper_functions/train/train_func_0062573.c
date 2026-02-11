rva_swap(fs_rid_vector **v, int count, int a, int b)
{
    fs_rid tmp;

    for (int i=0; i<count; i++) {
	tmp = v[i]->data[a];
	v[i]->data[a] = v[i]->data[b];
	v[i]->data[b] = tmp;
    }
}
