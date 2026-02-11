assign_out_of_memory()
{
    if (r_.cap > 0)
	delete[] reinterpret_cast<char*>(r_.s - memo_space);
    r_.s = reinterpret_cast<unsigned char*>(const_cast<char*>(String_generic::empty_data));
    r_.cap = -1;
    r_.len = 0;
}
