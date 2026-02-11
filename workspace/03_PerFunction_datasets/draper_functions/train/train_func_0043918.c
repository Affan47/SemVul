deleteChild(Curses *child)
{
	vector<Child>::iterator b=children.begin(), e=children.end();

	while (b != e)
	{
		Child &c= *b;

		if (c.child == child)
		{
			child->setParent(0);
			children.erase(b, b+1);
			break;
		}
		b++;
	}
}
