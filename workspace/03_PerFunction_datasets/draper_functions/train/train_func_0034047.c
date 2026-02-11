cleanup(CleanupStage)
{
    for (int i = _head; i != _tail; i = next_i(i))
	_q[i]->kill();
    CLICK_LFREE(_q, sizeof(Packet *) * (_capacity + 1));
    _q = 0;
}
