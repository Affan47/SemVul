update(unsigned int iteration)
{
    if (iteration < _start || (iteration - _start) % _thin != 0) {
	return;
    }
    else {
	_monitor->update();
	_niter++;
    }
}
