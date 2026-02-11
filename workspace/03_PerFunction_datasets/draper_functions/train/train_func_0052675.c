copy_order(Dllist *dll, const int SRC, const int DEST)
{


	Vertex *temp = dll->root;
	for (int i = 0; i <= dll->length; i++)
	{
		temp->links[DEST][FWD] = temp->links[SRC][FWD];
		temp->links[DEST][BWD] = temp->links[SRC][BWD];
		temp = temp->links[SRC][FWD];
	}
	dll->length = dll->length;
}
