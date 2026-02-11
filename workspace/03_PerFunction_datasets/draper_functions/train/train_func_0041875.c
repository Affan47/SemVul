search(ht_search_request *search, FileOfs start, FileOfs end)
{
	if (collapsed) return NULL;
	return ht_layer_sub::search(search, start, end);
}
