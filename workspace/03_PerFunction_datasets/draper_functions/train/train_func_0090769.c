remove(int which)
{
    if ((*this)[which] != NULL)
	(*this)[which]->unref();

    QvPList::remove(which);
}
