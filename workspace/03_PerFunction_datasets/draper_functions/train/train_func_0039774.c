elementAnimationFinished()
{
    if (autohide && state == FlashingLabelPrivate::Invisible && anim.data()) {
        q->hide();
    }
}
