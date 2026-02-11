resize_dynarray(dynarray *this, long newsize)
{
    if (!this->v)
	graph_error("resize_dynarray: dynarray wasn't initialized!");

    if (newsize == 0)
	free_dynarray(this);
    else {
	this->v = gp_realloc(this->v, this->entry_size * newsize, "extend dynarray");
	this->size = newsize;
    }
}
