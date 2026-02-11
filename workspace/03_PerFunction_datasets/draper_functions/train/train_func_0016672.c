world_food_eat(int x, int y, int amount) {
    if (!world_is_on_map(x, y))
        return 0;

    if (MAPTILE(x, y).type != TILE_PLAIN)
        return 0;

    int ontile = MAPTILE(x, y).food;
    if (amount > ontile)
        amount = ontile;

    int old = MAPTILE(x, y).food;
    int new = MAPTILE(x, y).food -= amount;

    if (food_to_network_food(new) != food_to_network_food(old))
        world_to_network(x, y, SEND_BROADCAST);

    return amount;
}
