MarkDragPointForDeletion()
{
   mIsDeleting = true;


   if( mEnv.Count()<=1)
   {


      mEnv[mDragPoint]->SetT(-1000000.0);
      mEnv[mDragPoint]->SetVal(mDefaultValue);
      return;
   }


   int iNeighbourPoint = mDragPoint + ((mDragPoint > 0) ? -1:+1);
   mEnv[mDragPoint]->SetT(mEnv[iNeighbourPoint]->GetT());
   mEnv[mDragPoint]->SetVal(mEnv[iNeighbourPoint]->GetVal());
}
