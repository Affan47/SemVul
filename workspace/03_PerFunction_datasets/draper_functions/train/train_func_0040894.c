finishProlog()
{
  if (root_->prolog)
    addBarrier();
  tailPtr_ = 0;
}
