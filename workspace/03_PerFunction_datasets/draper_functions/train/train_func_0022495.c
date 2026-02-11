_in_node_bit_list(int inx, int *node_list_array)
{
	int i;
	bool rc = false;

	for (i=0; ; i+=2) {
		if (node_list_array[i] == -1)
			break;
		if ((inx >= node_list_array[i]) &&
		    (inx <= node_list_array[i+1])) {
			rc = true;
			break;
		}
	}

	return rc;
}
