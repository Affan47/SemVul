checkBufferStructure()
{
	Buffer const * master = buffer()->masterBuffer();
	master->tocBackend().updateItem(*this);
	if (master != buffer() && !master->hasGuiDelegate())


		buffer()->tocBackend().updateItem(*this);
}
