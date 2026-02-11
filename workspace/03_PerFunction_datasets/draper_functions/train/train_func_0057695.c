pull(int)
{

    Storage::index_type h = _head, t = _tail, nh = next_i(h);

    if (h != t)
	return pull_success(h, nh);
    else
	return pull_failure();
}
