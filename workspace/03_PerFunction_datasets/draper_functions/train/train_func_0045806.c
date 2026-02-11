store_item_increase(int st, int item, int num)
{
	int cnt;
	object_type *o_ptr;

	store_type *st_ptr = &store[st];


	o_ptr = &st_ptr->stock[item];


	cnt = o_ptr->number + num;
	if (cnt > 255) cnt = 255;
	else if (cnt < 0) cnt = 0;


	o_ptr->number = cnt;
}
