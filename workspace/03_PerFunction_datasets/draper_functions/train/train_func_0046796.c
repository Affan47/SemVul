bindImpl()
{
	{
		Poco::Data::AbstractBindingVec& binds = bindings();
		size_t pos = 0;
		Poco::Data::AbstractBindingVec::iterator it = binds.begin();
		Poco::Data::AbstractBindingVec::iterator itEnd = binds.end();

		for (; it != itEnd && (*it)->canBind(); ++it)
		{
			(*it)->bind(pos);
			pos += (*it)->numOfColumnsHandled();
		}
	}

	_stmt.bindParams(_binder.getBindArray(), _binder.size());

	_stmt.execute();

	_hasNext = NEXT_DONTKNOW;
}
