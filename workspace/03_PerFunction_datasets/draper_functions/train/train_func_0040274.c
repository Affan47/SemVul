NotifyDone()
{
    if (!notify_ || !notifyer_) return true;

    return notifyer_->Notify(-1);
}
