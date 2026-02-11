ReparentExtraPanel()
{


   wxPoint pos;
   pos.x = mGrabberSize.x;
   pos.y = mMainSize.y + mButtonSize.y;
   wxWindow *frame = this;
   while(!frame->IsTopLevel()) {
      pos += frame->GetPosition();
      frame = frame->GetParent();
   }

   mExtraPanel->Reparent(frame);
   mExtraPanel->SetPosition(pos);
}
