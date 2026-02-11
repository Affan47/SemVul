possible_mmc (byte *msg, size_t msglen)
{
	if (!MachineControl::is_mmc (msg, msglen)) {
		return false;
	}


	if (!_offline) {
		mmc (*this, &msg[1], msglen - 1);
	}

	return true;
}
