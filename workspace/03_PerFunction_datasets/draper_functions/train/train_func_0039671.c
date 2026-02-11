ExpandRow(int rowIndex)
{


   wxSize area = GetClientSize();
   int i, j, x;
   int minWidth = 0;
   int leftoverSpace = 0;
   int expandableCount = 0;
   int toolbarCount = 0;

   for(i=0; i<(int)mChildArray.GetCount(); i++)
      if (mRowArray[i] == rowIndex) {
         ExpandingToolBar *child = mChildArray[i];
         wxSize childMin = child->GetMinSize();
         wxSize childMax = child->GetMaxSize();

         minWidth += childMin.x;

         toolbarCount++;
         if (childMax.x > childMin.x)
            expandableCount++;
      }

   leftoverSpace = area.x - minWidth;

   if (leftoverSpace <= 0) {
      if (toolbarCount > 1)
         return false;
      else
         return true;
   }

   j = 0;
   x = 0;
   for(i=0; i<(int)mChildArray.GetCount(); i++)
      if (mRowArray[i] == rowIndex) {
         ExpandingToolBar *child = mChildArray[i];
         wxPoint childPos = child->GetPosition();
         wxSize childMin = child->GetMinSize();
         wxSize childMax = child->GetMaxSize();

         int width = childMin.x;

         if (childMax.x > childMin.x)
            width +=
               (leftoverSpace * (j+1) / expandableCount) -
               (leftoverSpace * (j) / expandableCount);

         mChildArray[i]->SetSize(x, childPos.y,
                                 width, childMin.y);
         x += width;
         j++;
      }

   return true;
}
