update_slots_callback(PyTypeObject *type, void *data)
{
    slotdef **pp = (slotdef **)data;

    for (; *pp; pp++)
        update_one_slot(type, *pp);
    return 0;
}
