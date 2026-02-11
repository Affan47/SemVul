DefaultOrders()
{
	forlist((&objects)) {
		Object *obj = (Object *) elem;
		forlist ((&obj->units))
			((Unit *) elem)->DefaultOrders(obj);
	}
}
