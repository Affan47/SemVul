_PyNode_SizeOf(node *n)
{
    Py_ssize_t res = 0;

    if (n != NULL)
        res = sizeof(node) + sizeofchildren(n);
    return res;
}
