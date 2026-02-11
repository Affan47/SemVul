IsAssignOp(const int x)
{
    return (outArray[x]==assign||outArray[x]==addassign
          ||outArray[x]==subassign||outArray[x]==multassign
          ||outArray[x]==divassign);
}
