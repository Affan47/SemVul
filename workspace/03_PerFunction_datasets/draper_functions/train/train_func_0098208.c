Grow ( void )

{
    vp  *save = array;
    int  anz  = elements,
         next = nextfree;

    Init(elements + increment,increment,free);

    nextfree = next;

    memcpy(array,save,anz * sizeof(vp));

    delete save;
}
