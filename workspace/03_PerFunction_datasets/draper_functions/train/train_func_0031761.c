new_map(void)
{
    static Var map;

    if (map.v.tree == NULL)
	map = empty_map();

    addref(map.v.tree);

    return map;
}
