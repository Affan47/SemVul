clipMode(MSClipMode clipMode_)
{
  if (clipMode()!=clipMode_ && clipMode_!=MSClipIndicator)
   {
     _clipMode=clipMode_;
     redraw();
   }
}
