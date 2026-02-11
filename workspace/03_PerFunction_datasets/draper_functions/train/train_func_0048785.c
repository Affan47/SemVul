BSTree_set(BSTree *map, void *key, void *data)
{
    if(map->root == NULL) {

        map->root = BSTree_node_create(NULL, key, data);
        check_mem(map->root);
    } else {
        BSTree_setnode(map, map->root, key, data);
    }

    return 0;
error:
    return -1;
}
