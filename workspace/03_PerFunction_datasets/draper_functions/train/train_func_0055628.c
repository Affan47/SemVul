IS_BAG (
    UInt                bid )
{
    return (((UInt)MptrBags <= bid)
         && (bid < (UInt)OldBags)
         && (bid & (sizeof(Bag)-1)) == 0);
}
