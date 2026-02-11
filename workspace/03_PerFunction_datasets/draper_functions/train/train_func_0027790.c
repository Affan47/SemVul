_PyAccu_Init(_PyAccu *acc)
{

    acc->large = NULL;
    acc->small = PyList_New(0);
    if (acc->small == NULL)
        return -1;
    return 0;
}
