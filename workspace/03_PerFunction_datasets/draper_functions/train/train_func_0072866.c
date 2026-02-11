GenerateTraversalTable()
{
  int xChild, yChild, zChild;
  int xCursor, yCursor, zCursor;
  int xNeighbor, yNeighbor, zNeighbor;
  int xNewCursor, yNewCursor, zNewCursor;
  int xNewChild, yNewChild, zNewChild;
  int cursor, child, newCursor, newChild;

  for (zChild = 0; zChild < 2; ++zChild)
    {
    for (yChild = 0; yChild < 2; ++yChild)
      {
      for (xChild = 0; xChild < 2; ++xChild)
        {
        for (zCursor = 0; zCursor < 2; ++zCursor)
          {
          for (yCursor = 0; yCursor < 2; ++yCursor)
            {
            for (xCursor = 0; xCursor < 2; ++xCursor)
              {


              xNeighbor = xCursor + xChild;
              yNeighbor = yCursor + yChild;
              zNeighbor = zCursor + zChild;

              xNewCursor = xNeighbor / 2;
              yNewCursor = yNeighbor / 2;
              zNewCursor = zNeighbor / 2;
              xNewChild = xNeighbor - xNewCursor*2;
              yNewChild = yNeighbor - yNewCursor*2;
              zNewChild = zNeighbor - zNewCursor*2;

              cursor = xCursor + 2*yCursor + 4*zCursor;
              child = xChild + 2*yChild + 4*zChild;

              newCursor = xNewCursor + 2*yNewCursor + 4*zNewCursor;
              newChild = xNewChild + 2*yNewChild + 4*zNewChild;
              this->NeighborhoodTraversalTable[8*child + cursor]
                      = newChild+ 8*newCursor;
              }
            }
          }
        }
      }
    }
}
