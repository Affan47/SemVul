ai_resize(alloc_info *ai, int new_size)
{
	if(new_size < 0)
		return false;


	if(new_size == 0)
	{

		if(ai->size > 0)
		{
			if(ai->sec)
			{
				delete ai->sbuf;
				ai->sbuf = 0;
			}
			else
			{
				delete ai->qbuf;
				ai->qbuf = 0;
			}

			ai->size = 0;
			ai->data = 0;
		}

		return true;
	}

	if(ai->sec)
	{
		Botan::SecureVector<Botan::byte> *new_buf;
		try
		{
			new_buf = new Botan::SecureVector<Botan::byte>((Botan::u32bit)new_size + 1);
		}
		catch(std::exception &)
		{
			botan_throw_abort();
			return false;
		}

		Botan::byte *new_p = (Botan::byte *)(*new_buf);
		if(ai->size > 0)
		{
			const Botan::byte *old_p = (const Botan::byte *)(*(ai->sbuf));
			memcpy(new_p, old_p, qMin(new_size, ai->size));
			delete ai->sbuf;
		}
		ai->sbuf = new_buf;
		ai->size = new_size;
		(*(ai->sbuf))[new_size] = 0;
		ai->data = (char *)new_p;
	}
	else
	{
		if(ai->size > 0)
			ai->qbuf->resize(new_size);
		else
			ai->qbuf = new QByteArray(new_size, 0);

		ai->size = new_size;
		ai->data = ai->qbuf->data();
	}

	return true;
}
