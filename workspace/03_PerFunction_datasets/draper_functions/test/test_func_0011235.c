bkcycle() {
    if (_obs->intvalue()-1 < 0)
	_obs->setvalue(_obs->maxvalue()-1);
    else
	_obs->setvalue(_obs->intvalue()-1);
}
