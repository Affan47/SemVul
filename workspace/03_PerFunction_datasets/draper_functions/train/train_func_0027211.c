checkMutableLists (void)
{
    nat i;
    for (i = 0; i < n_capabilities; i++) {
        checkLocalMutableLists(i);
    }
}
