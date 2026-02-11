checkSanity (rtsBool after_gc, rtsBool major_gc)
{
    checkFullHeap(after_gc && major_gc);

    checkFreeListSanity();


    if (after_gc) {
        checkMutableLists();
        checkGlobalTSOList(rtsTrue);
    }
}
