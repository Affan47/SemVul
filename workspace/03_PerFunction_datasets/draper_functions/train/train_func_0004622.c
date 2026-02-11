size_box(BOX *box)
{
	if (box->high.x <= box->low.x || box->high.y <= box->low.y)
		return 0.0;
	return (box->high.x - box->low.x) * (box->high.y - box->low.y);
}
