_assign(const_iterator begin_, const_iterator end_)
	{
		assert(begin_ <= end_);

		size_t size_ = static_cast<size_t>(end_ - begin_);

		if (size_ <= 1)
		{

			if (_begin != &_storage) impl::xml_memory::deallocate(_begin);


			if (begin_ != end_) _storage = *begin_;

			_begin = &_storage;
			_end = &_storage + size_;
		}
		else
		{

			xpath_node* storage = static_cast<xpath_node*>(impl::xml_memory::allocate(size_ * sizeof(xpath_node)));

			if (!storage)
			{
			#ifdef PUGIXML_NO_EXCEPTIONS
				return;
			#else
				throw std::bad_alloc();
			#endif
			}

			memcpy(storage, begin_, size_ * sizeof(xpath_node));


			if (_begin != &_storage) impl::xml_memory::deallocate(_begin);


			_begin = storage;
			_end = storage + size_;
		}
	}
