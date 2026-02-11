interesting_to_discover(int i)
{

    return ((objects[i].oc_uname != NULL ||
             (objects[i].oc_name_known && OBJ_DESCR(objects[i]) != NULL)));
}
