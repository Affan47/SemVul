PixmapSprite(int no, QGraphicsScene* canvas)
    :  Themeable(), QGraphicsPixmapItem(0, canvas)
{
  hide();

  mAnimationState = Idle;
  mNo             = no;
  mCurrentFrame   = 0;
  mOffsetStatus   = true;
}
