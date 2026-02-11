assignHostId(int id) const {
	Must(hostId_ == INT_MIN && id != INT_MIN);
	hostId_ = id;
}
