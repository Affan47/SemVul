operator--()
	{
		if (_wrap._root)
			_wrap = _wrap.previous_sibling(_name);
		else
		{
			_wrap = _parent.last_child();

			if (!impl::strequal(_wrap.name(), _name))
				_wrap = _wrap.previous_sibling(_name);
		}

		return *this;
	}
